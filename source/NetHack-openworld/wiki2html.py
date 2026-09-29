#!/usr/bin/env python3
"""Turn the Markdown pages of the NetHack: Open World wiki into HTML.

usage: wiki2html.py <wiki directory> <output directory>

Only the Markdown that the wiki uses is supported: ATX headings (with
GitHub-style anchors), paragraphs, nested bullet and numbered lists, pipe
tables, fenced code blocks, block quotes, `code`, **bold**, *italic* and
[links](Page.md#anchor), with links to other pages rewritten to .html.
No third-party modules are needed.
"""
import html
import os
import re
import sys

STYLE = """
:root { --bg: #fdfcf8; --fg: #222; --muted: #666; --link: #1f5fa8;
        --rule: #d8d4c8; --code: #f1eee4; --th: #ece8dc; }
@media (prefers-color-scheme: dark) {
  :root { --bg: #1b1d21; --fg: #ddd; --muted: #999; --link: #7fb2ee;
          --rule: #3a3d44; --code: #272a30; --th: #2a2d33; }
}
body { background: var(--bg); color: var(--fg); margin: 0 auto;
       max-width: 900px; padding: 1.5em 16px 4em;
       font: 16px/1.55 -apple-system, "Segoe UI", Helvetica, Arial, sans-serif; }
a { color: var(--link); }
h1, h2, h3, h4 { line-height: 1.25; margin: 1.6em 0 0.6em; }
h1 { font-size: 1.9em; margin-top: 0.4em; }
h2 { border-bottom: 1px solid var(--rule); padding-bottom: 0.2em; }
code, pre { background: var(--code); border-radius: 4px;
            font: 0.92em/1.4 Menlo, Consolas, monospace; }
code { padding: 0.1em 0.3em; }
pre { padding: 0.8em 1em; overflow-x: auto; }
pre code { padding: 0; background: none; }
table { border-collapse: collapse; margin: 1em 0; display: block;
        overflow-x: auto; }
th, td { border: 1px solid var(--rule); padding: 0.35em 0.6em;
         vertical-align: top; text-align: left; }
th { background: var(--th); }
blockquote { margin: 1em 0; padding: 0.2em 1em; color: var(--muted);
             border-left: 4px solid var(--rule); }
li { margin: 0.2em 0; }
footer { margin-top: 3em; color: var(--muted); font-size: 0.85em; }
"""


def slug(text):
    """GitHub's anchor for a heading."""
    s = re.sub(r'<[^>]+>', '', text).strip().lower()
    s = re.sub(r'[^\w\- ]', '', s)
    return s.replace(' ', '-')


def inline(text):
    """Render the inline markup of one line or paragraph of text."""
    codes = []

    def keep_code(m):
        codes.append('<code>%s</code>' % html.escape(m.group(1)))
        return '\x00%d\x00' % (len(codes) - 1)

    text = re.sub(r'`([^`]+)`', keep_code, text)
    text = html.escape(text, quote=False)

    def link(m):
        label, target = m.group(1), m.group(2)
        if not re.match(r'[a-z]+:', target):
            target = re.sub(r'\.md(?=$|#)', '.html', target)
        return '<a href="%s">%s</a>' % (html.escape(target), label)

    text = re.sub(r'\[([^\]]+)\]\(([^)\s]+)\)', link, text)
    text = re.sub(r'\*\*(.+?)\*\*', r'<strong>\1</strong>', text)
    text = re.sub(r'(?<![\w*])\*(?!\s)(.+?)(?<!\s)\*(?![\w*])',
                  r'<em>\1</em>', text)
    return re.sub('\x00(\\d+)\x00', lambda m: codes[int(m.group(1))], text)


LIST_ITEM = re.compile(r'^(\s*)([*-]|\d+\.)\s+(.*)$')


def indent_of(line):
    return len(line) - len(line.lstrip(' '))


def parse_list(lines, i, base):
    """Parse a (possibly nested) list whose markers are indented by
    'base'; returns (html, next line index)."""
    items, ordered = [], False
    while i < len(lines):
        line = lines[i]
        if not line.strip():
            j = i
            while j < len(lines) and not lines[j].strip():
                j += 1
            if j < len(lines) and (indent_of(lines[j]) > base
                                   or (LIST_ITEM.match(lines[j])
                                       and indent_of(lines[j]) == base)):
                i = j
                continue
            break
        m = LIST_ITEM.match(line)
        ind = indent_of(line)
        if m and ind == base:
            ordered = m.group(2)[0].isdigit()
            items.append([['text', m.group(3).strip()]])
            i += 1
        elif m and ind > base and items:
            sub, i = parse_list(lines, i, ind)
            items[-1].append(['html', sub])
        elif (not m and ind > base and items
              and line.lstrip().startswith('|')):
            # a table inside a list item
            rows = []
            while i < len(lines) and lines[i].lstrip().startswith('|'):
                rows.append(lines[i].strip())
                i += 1
            items[-1].append(['html', table(rows)])
        elif not m and ind > base and items:
            if items[-1][-1][0] == 'text':
                items[-1][-1][1] += ' ' + line.strip()
            else:
                items[-1].append(['text', line.strip()])
            i += 1
        else:
            break
    tag = 'ol' if ordered else 'ul'
    out = ['<%s>' % tag]
    for parts in items:
        body = ''.join(inline(p) if kind == 'text' else '\n' + p + '\n'
                       for kind, p in parts)
        out.append('<li>%s</li>' % body)
    out.append('</%s>' % tag)
    return '\n'.join(out), i


def table(rows):
    """Render a pipe table: header row, separator row, body rows."""
    out = ['<table><thead><tr>%s</tr></thead><tbody>'
           % ''.join('<th>%s</th>' % inline(c) for c in cells(rows[0]))]
    for row in rows[2:]:
        out.append('<tr>%s</tr>' % ''.join('<td>%s</td>' % inline(c)
                                           for c in cells(row)))
    out.append('</tbody></table>')
    return '\n'.join(out)


def cells(row):
    row = row.strip()
    if row.startswith('|'):
        row = row[1:]
    if row.endswith('|'):
        row = row[:-1]
    return [c.strip() for c in row.split('|')]


def render(md):
    lines = md.split('\n')
    out, i, title = [], 0, None
    while i < len(lines):
        line = lines[i]
        if not line.strip():
            i += 1
        elif line.startswith('```'):
            j = i + 1
            while j < len(lines) and not lines[j].startswith('```'):
                j += 1
            out.append('<pre><code>%s</code></pre>'
                       % html.escape('\n'.join(lines[i + 1:j])))
            i = j + 1
        elif re.match(r'#{1,6} ', line):
            level = len(line) - len(line.lstrip('#'))
            text = inline(line[level:].strip())
            if title is None:
                title = re.sub(r'<[^>]+>', '', text)
            out.append('<h%d id="%s">%s</h%d>'
                       % (level, slug(line[level:]), text, level))
            i += 1
        elif (line.lstrip().startswith('|') and i + 1 < len(lines)
              and re.match(r'^\s*\|?\s*:?-+', lines[i + 1])):
            rows = []
            while i < len(lines) and lines[i].lstrip().startswith('|'):
                rows.append(lines[i].strip())
                i += 1
            out.append(table(rows))
        elif line.startswith('>'):
            quote = []
            while i < len(lines) and lines[i].startswith('>'):
                quote.append(lines[i][1:].lstrip())
                i += 1
            out.append('<blockquote><p>%s</p></blockquote>'
                       % inline(' '.join(quote)))
        elif LIST_ITEM.match(line):
            block, i = parse_list(lines, i, indent_of(line))
            out.append(block)
        else:
            para = []
            while (i < len(lines) and lines[i].strip()
                   and not LIST_ITEM.match(lines[i])
                   and not re.match(r'#{1,6} |```|>|\s*\|', lines[i])):
                para.append(lines[i].strip())
                i += 1
            out.append('<p>%s</p>' % inline(' '.join(para)))
    return title or 'NetHack: Open World wiki', '\n'.join(out)


def main():
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    src, dst = sys.argv[1], sys.argv[2]
    os.makedirs(dst, exist_ok=True)
    pages = sorted(f for f in os.listdir(src) if f.endswith('.md'))
    for name in pages:
        with open(os.path.join(src, name), encoding='utf-8') as f:
            title, body = render(f.read())
        page = ('<!doctype html>\n<html lang="en">\n<head>\n'
                '<meta charset="utf-8">\n'
                '<meta name="viewport" content="width=device-width, '
                'initial-scale=1">\n'
                '<title>%s — NetHack: Open World</title>\n'
                '<style>%s</style>\n</head>\n<body>\n%s\n'
                '<footer>NetHack: Open World supplemental wiki · '
                '<a href="Home.html">Home</a></footer>\n</body>\n</html>\n'
                % (html.escape(title), STYLE, body))
        with open(os.path.join(dst, name[:-3] + '.html'), 'w',
                  encoding='utf-8') as f:
            f.write(page)
    print('wiki: %d pages -> %s' % (len(pages), dst))


if __name__ == '__main__':
    main()
