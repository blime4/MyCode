# coding: utf-8 

import scrapy
from scrapy import Spider,Selector,Request
from scrapy.linkextractors import LinkExtractor
from scrapy.spiders import CrawlSpider, Rule
from ..items import ProxyItem


class XiciSpider(scrapy.Spider):
    name = 'xici'
    allowed_domains = ['xicidaili.com']
    start_urls = ['http://xicidaili.com/wt/1']

    rules = (
        Rule(LinkExtractor(allow=r'/wt/*',),follow=True,callback='parse_items'),
    )
    
            
    def parse_items(self, response):
        selector = Selector(response)
        row_selectors = selector.xpath('//tr')
        
        for row_selector in row_selectors:
            item = ProxyItem()
            item['ip'] = row_selector.xpath('td[2]/text()').extract_first()
            item['protocol'] = row_selector.xpath('td[6]/text()').extract_first().lower()
            item['port'] = int(row_selector.xpath('td[3]/text()').extract_first())
            connection_time_str = row_selector.xpath('td[8]/div/@title').extract_first()
            item['connection_time']= _duration_to_milliseconds(connection_time_str)
            item['speed']= _duration_to_milliseconds(row_selector.xpath('td[7]/div/@title').extract_first)
            item['ttl']= _duration_to_milliseconds(row_selector.xpath('td[9]/text()').extract_first)
            item['validated'] = row_selector.xpath('td[10]/text()').extract_first()
            yield item
            
             
            
        def _duration_to_milliseconds(val):
            print(val)
            return val
            
