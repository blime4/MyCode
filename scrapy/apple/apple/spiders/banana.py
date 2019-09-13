# -*- coding: utf-8 -*-
import scrapy


class BananaSpider(scrapy.Spider):
    name = 'banana'
    allowed_domains = ['https://movie.douban.com/review/best/']
    start_urls = ['https://movie.douban.com/review/best/']

    def parse(self, response):
        articles = response.xpath("//div[@class='review-list chart']/div")
        for article in articles:
            author = article.xpath(".//header/a[@class='name']/text()").get()
            print(author)
