
import pygame
import time


h = input("���������ӵ�ʱ�ͷ֣��ÿո�ָ���").split(' ')


while True:
    
    t = time.localtime()
    now = time.strftime("%H %M",t).split(' ')
    if h[0] == now[0] and h[1] == now[1]:
        print("ʱ�䵽��")
        pygame.mixer.init()
        track = pygame.mixer.Sound("Lovestoned - Byebyebye.wav")
        track.play()
        