
import pygame
import time


h = input("请输入闹钟的时和分，用空格分隔：").split(' ')


while True:
    
    t = time.localtime()
    now = time.strftime("%H %M",t).split(' ')
    if h[0] == now[0] and h[1] == now[1]:
        print("时间到！")
        pygame.mixer.init()
        track = pygame.mixer.Sound("Lovestoned - Byebyebye.wav")
        track.play()
        