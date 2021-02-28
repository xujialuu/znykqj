# -*- coding:utf-8 -*-
from aip import AipFace
import urllib.request
import base64
import time
import os
import time

#百度人脸识别API账号信息
APP_ID = '23719753'
API_KEY = 'VXfflNoZ74Q8mL1qEiqawtwC'
SECRET_KEY ='gomGx893iUzX3axkahwVULdToTQ1Wqha'
client = AipFace(APP_ID, API_KEY, SECRET_KEY)#创建一个客户端用以访问百度云
#图像编码方式
IMAGE_TYPE='BASE64'
#用户组
GROUP = '1'

#对图片的格式进行转换
def transimage():
    f = open('camera.jpeg','rb')
    img = base64.b64encode(f.read())
    return img

#上传到百度api进行人脸检测
def go_api(image):
    result = client.search(str(image, 'utf-8'), IMAGE_TYPE, GROUP);#在百度云人脸库中寻找有没有匹配的人脸
    if result['error_msg'] == 'SUCCESS':#如果成功了
        name = result['result']['user_list'][0]['user_id']#获取名字
        score = result['result']['user_list'][0]['score']#获取相似度
        if score > 80:#如果相似度大于80
            if name == 'Azis':
                print("欢迎%s !" % name)
                time.sleep(3)
        else:
            print("对不起，我不认识你！")
            name = 'Unknow'
            return 0
        curren_time = time.asctime(time.localtime(time.time()))#获取当前时间
 
        #将人员出入的记录保存到Log.txt中
        f = open('Log.txt','a')
        f.write("Person: " + name + "     " + "Time:" + str(curren_time)+'\n')
        f.close()
        return 1
    if result['error_msg'] == 'pic not has face':
        print('检测不到人脸')
        time.sleep(2)
        return 0
    else:
        print(result['error_code']+' ' + result['error_code'])
        return 0
#主函数

def main():
    while True:
        print('准备进行识别')
        
        if True:
            img = transimage()#转换照片格式
            res = go_api(img)#将转换了格式的图片上传到百度云
            if(res == 1):#是人脸库中的人
                time.sleep(0.5)
                print("识别成功，允许通行")
            else:
                print("识别失败，禁止通行")
            print('稍等三秒进行下一次识别')
            time.sleep(3)

if __name__ == '__main__':
    main()