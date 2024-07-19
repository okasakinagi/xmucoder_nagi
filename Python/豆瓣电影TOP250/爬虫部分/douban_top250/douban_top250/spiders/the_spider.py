import scrapy
import re
from douban_top250.items import MovieItem


class TheSpiderSpider(scrapy.Spider):
    name = "the_spider"
    allowed_domains = ["movie.douban.com"]

    def start_requests(self):
        for page in range(10):
            yield scrapy.Request(
                f"https://movie.douban.com/top250?start={25*page}&filter="
            )

    def parse(self, response):
        sel = scrapy.Selector(response)
        list_items = sel.css("#content > div > div.article > ol > li")
        for item in list_items:
            detial_url = item.css("div.info > div.hd > a::attr(href)").get()
            movie_item = MovieItem()
            movie_item["title"] = item.css("span.title::text").get()
            movie_item["rank"] = item.css("span.rating_num::text").get()
            movie_item["theme"] = item.css("span.inq::text").get()  # 主旨
            yield scrapy.Request(
                detial_url, callback=self.parse_detail, cb_kwargs={"item": movie_item}
            )

    def parse_detail(self, response, **kwargs):
        movie_item = kwargs["item"]
        sel = scrapy.Selector(response)
        items = (
            re.search(
                r"制片国家/地区\D{4,}\n",
                str(sel.css("#info").get()).replace("</span>", "").replace("<br>", ""),
            )
            .group()
            .split(":")[1]
            .strip()
            .split("\n")[0]
        )
        # items = str(sel.css("#info").get()).replace("</span>", "").replace("<br>", "")
        movie_item["nationality"] = items
        yield movie_item
