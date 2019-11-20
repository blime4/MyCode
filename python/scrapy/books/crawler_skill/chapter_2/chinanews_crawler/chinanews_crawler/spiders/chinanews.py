# -*- coding: utf-8 -*-
import scrapy
from bs4 import BeautifulSoup
from scrapy import Spider
from ..items import FeedItem
import json
class ChinanewsSpider(Spider):
    name = 'chinanews'
    allowed_domains = ['chinanews.com']
    start_urls = ["http://www.chinanews.com/rss/scroll-news.xml"]

    def parse(self, response):
        rss = BeautifulSoup(response.body, 'html.parser')
        for item in rss.find_all('item'):
            feed_item = FeedItem()
            feed_item['title'] = item.title.text
            feed_item['link'] = item.link.text
            feed_item['desc'] = item.description.text
            feed_item['pub_date'] = item.pubdate.text
            yield feed_item
            
