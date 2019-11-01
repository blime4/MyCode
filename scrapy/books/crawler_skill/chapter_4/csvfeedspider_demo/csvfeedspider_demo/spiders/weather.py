# -*- coding: utf-8 -*-
import scrapy
from ..items import City
from scrapy.spiders import CSVFeedSpider
from cities import names

class WeatherSpider(scrapy.Spider):
    name = 'weather'
    allowed_domains = ['beijingair.sinaapp.com']
    start_urls = ['http://beijingair.sinaapp.com/data/china/cities/20171220/csv']

    def parse(self, response):
        city = City()
        for name in names:
            if row[name] != None:
                city['name'] = name
                city