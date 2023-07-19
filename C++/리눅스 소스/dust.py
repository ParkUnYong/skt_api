#-*- coding:utf-8 -*-
#Python3

import json
import requests

#params = {"version": "1", "city":"서울", "county":"중랑구","village":"면목동"}
params = {"version" : 1, "lat":"37.5866170", "lon":"127.0977440"}
headers = {"appKey": "572ce589-6bbe-3c60-a4d3-d8ed9a8272c1"}

r_weath = requests.get("http://apis.skplanetx.com/weather/current/minutely", params=params, headers=headers)

#json -> python 객체로 변환
data_weath = json.loads(r_weath.text)
tmp_weath = data_weath["weather"]["minutely"]
weath_time = tmp_weath[0]["timeObservation"]
weath_sky = tmp_weath[0]["sky"]["name"]
weath_temper = tmp_weath[0]["temperature"]["tc"]

str_weather = "오늘의 날씨\n"+weath_time+" 기준, 하늘은 '" +weath_sky+ "'상태이고 기온은 " + weath_temper + "입니다.\n"
print(str_weather)
