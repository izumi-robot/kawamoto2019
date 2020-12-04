__all__ = ['md2html']


import os
import os.path
import sys
import re
import mistune
from pygments import highlight
from pygments.lexers import get_lexer_by_name
from pygments.formatters.html import HtmlFormatter


class MyRenderer(mistune.Renderer):
    def __init__(self):
        super().__init__()
        self.formatter = HtmlFormatter(cssclass='hll')

    def convert(self, text):
        res = mistune.markdown(text, renderer=self)
        if res.startswith('<p>') and res.endswith('</p>\n'):
            res = res[3:-5]
        return res

    def header(self, text, level, raw=None):
        h = super().header(text, level)
        if not raw:
            return h
        r = (raw
            .replace('(', '')
            .replace(')', '')
            .replace('.', '')
            .replace(' ', '-')
        )
        return h.replace(
            f'<h{level}>',
            f'<h{level} id="{r}">',
            1
        )

    def block_code(self, code, lang=None):
        try:
            l, _, filename = lang.partition(':')
        except AttributeError:
            l, filename = '', ''

        try:
            lexer = get_lexer_by_name(l)
        except:
            res = f'\n<div class="hll"><pre>{code}</pre></div>\n'
        else:
            res = highlight(code, lexer, self.formatter)

        if filename:
            new = f'<pre><span class="file">{filename}</span>\n\n'
        else:
            new = '<pre>\n\n'
        res = res.replace('<pre>', new, 1)

        s1, s2, s3 = res.rpartition('</pre>')
        s1 += '\n' * (2 - s1.count("\n", -2))
        res = s1 + s2 + s3

        return res

    def inline_html(self, html):
        start_tag = re.findall('<.+?>', html)[0]
        try:
            end_tag = re.findall('</.+?>', html)[-1]
        except IndexError:
            return html
        sl, el = len(start_tag), len(end_tag)
        text = html[sl:-el]
        result = (
            start_tag
            + self.convert(text)
            + end_tag
        )
        return result

    block_html = inline_html


def _convert():
    renderer = MyRenderer()
    convertor = mistune.Markdown(renderer=renderer)
    def main(source):
        content = convertor(source)
        return content
    return main


def _md2html(dir='./'):
    global _convert
    with open(f'{dir}src/template.html', 'r', encoding='utf-8') as h,\
         open(f'{dir}src/style.css', 'r', encoding='utf-8') as c:
        template = h.read()
        style = c.read()
    template = template.replace('/* CSS */', style, 1)
    h1_ptn = re.compile('<h1.*?>.*?</h1>')
    intext_ptn = re.compile('>.*<')
    prop_ptn = re.compile('^---.+?---$', re.DOTALL | re.MULTILINE)
    convert = _convert()
    del _convert

    def get_title(html):
        h1 = h1_ptn.findall(html)[0]
        title = intext_ptn.findall(h1)[0]
        return title[1:-1]

    def main(source):
        if prop_ptn.match(source):
            tar = prop_ptn.findall(source)[0]
            #print(tar)
            source = source.replace(tar, '', 1)
        content = convert(source)
        result = template.replace('{{CONTENT}}', content)

        try:
            title = get_title(result)
        except IndexError:
            pass
        else:
            result = result.replace('Title', title, 1)

        return result

    return main


dir = os.path.dirname(__file__)
md2html = _md2html(dir)
del _md2html, dir


if __name__ == '__main__':
    with open('sample.md', 'r', encoding='utf-8') as f:
        source = f.read()

    out = md2html(source)
    with open('out.html', 'x', encoding='utf-8') as f:
        f.write(out)
