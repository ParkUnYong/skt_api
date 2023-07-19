#-*- coding:utf-8 -*-
#파이썬3으로 동작 시킬것

import json
import requests
import serial
import time

#params = {"version": "1", "city":"서울", "county":"중랑구","village":"면목동"}
params = {"version" : 1, "lat":"37.5866170", "lon":"127.0977440"}
headers = {"appKey": "572ce589-6bbe-3c60-a4d3-d8ed9a8272c1"}

ser = serial.Serial('COM3', 9600)

while True :
    r_weath = requests.get("http://apis.skplanetx.com/weather/current/minutely", params=params, headers=headers)
    r_dust = requests.get("http://apis.skplanetx.com/weather/dust", params=params, headers=headers)

    #json -> python 객체로 변환
    data_weath = json.loads(r_weath.text)
    tmp_weath = data_weath["weather"]["minutely"]
    weath_time = tmp_weath[0]["timeObservation"]
    weath_sky = tmp_weath[0]["sky"]["name"]
    #cSky_code = tmp_weath[0]["sky"]["code"]
    weath_temper = tmp_weath[0]["temperature"]["tc"]

    data_dust = json.loads(r_dust.text)
    tmp_dust = data_dust["weather"]["dust"]
    dust_time = tmp_dust[0]["timeObservation"]
    dust_value = tmp_dust[0]["pm10"]["value"]
    dust_grade = tmp_dust[0]["pm10"]["grade"]

    str_weather = "오늘의 날씨\n"+weath_time+" 기준, 하늘은 '" +weath_sky+ "'상태이고 기온은 " + weath_temper + "입니다.\n"
    str_dust = "오늘의 미세먼지\n"+dust_time+" 기준, 농도는 " +dust_value+ "이고 등급은 " +dust_grade+ "입니다.\n"

    print(str_weather)
    print(str_dust)

    tmp_dust_value = dust_value.zfill(5)

    for i in range(180) :
        #ser.write( tmp_dust_value.encode() )
        ser.write( "99.88".encode() )
        time.sleep(1)

    # 180일 경우 3분당 1번씩 요청. 하루 500번 제한 걸렸음
