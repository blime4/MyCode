# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy
from scrapy import Item,Field

class City(Item):
    name = Field()
    norm = Field()
    value = Field()
    date = Field()

class CsvfeedspiderDemoItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    pass
