import requests


def get_md(url: str) -> str:
    assert url.startswith("https://qiita.com")
    if not url.endswith('.md'):
        url += ".md"
    resp = requests.get(url)
    result = resp.content.decode('utf-8')