from urllib.request import urlopen
from bs4 import BeautifulSoup
import json

r = urlopen('http://www.chinanews.com/rss/rss_2.html')
r_page = BeautifulSoup(r.read(), 'html.parser')
rss_links = set([item['href'] for item in r_page.find_all('a')])

def crawl_feed(url):
    res = urlopen(url)
    rss = BeautifulSoup(res.read(), 'lxml')
    items = []
    print("Crawling %s" %url)
    
    for item in rss.find_all('item'):
        try:
            feed_item = {
                'title':item.title.text,
                'link':item.link.text,
                'desc':item.description.text,
                'pub_date':u'' if item.pubdate is None else item.pubdate.text
            }
            items.append(feed_item)
        except Exception as e:
            print('Crawling %s error: %s' % url)
            print(r.message)
    
    return items

feed_items = []

for link in rss_links:
    feed_items += crawl_feed(link)

with open('./result.json', 'a') as f:
    f.write(json.dumps(feed_items))

print('Total crawl %s items'%len(feed_items))       