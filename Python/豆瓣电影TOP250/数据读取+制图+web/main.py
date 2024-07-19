import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import flask
import sqlite3
import base64
from io import BytesIO


def make_graph():
    conn = sqlite3.connect("douban.db")
    c = conn.cursor()
    c.execute("SELECT * FROM DOUBAN_TOP250")
    Map = {}
    for row in c.fetchall():
        nations = row[4].split("/")
        for nation in nations:
            if nation.strip() in Map.keys():
                Map[nation.strip()] += 1
            else:
                Map[nation.strip()] = 1
    plt.rcParams["font.sans-serif"] = ["SimHei"]
    bar = plt.bar(Map.keys(), Map.values())
    plt.title("豆瓣TOP250电影制作国家或地区分布图")
    plt.xlabel("国家或地区")
    plt.ylabel("制作部数")
    plt.xticks(rotation=90)
    plt.bar_label(bar)
    buffer = BytesIO()
    plt.savefig(buffer, format="png", bbox_inches="tight")
    buffer.seek(0)
    image_png = buffer.getvalue()
    buffer.close()
    graph = base64.b64encode(image_png).decode("utf-8")
    conn.close()
    return graph


app = flask.Flask(__name__)
graph = make_graph()


@app.route("/", methods=["GET", "POST"])
def home():
    if flask.request.method == "GET":
        moviename = flask.request.args.get("moviename")
        if moviename != None:
            conn = sqlite3.connect("douban.db")
            c = conn.cursor()
            c.execute(f"SELECT * FROM DOUBAN_TOP250 WHERE title = '{moviename}'")
            row = c.fetchone()
            if row != None:
                string = f"电影名 = {row[1]}，电影评分 = {row[2]}，电影评价or金句 = “{row[3]}”，制作国家或地区= {row[4]}。"
            else:
                string = "该电影不在豆瓣TOP250排行榜中。"
            conn.close()
            kwargs = {"graph": graph, "Insert": string}
        else:
            kwargs = {"graph": graph}
    else:
        kwargs = {"graph": graph}
    return flask.render_template("index.html", **kwargs)


if __name__ == "__main__":
    app.run(debug=True)
