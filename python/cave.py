""" cave """
import sys
from random import randint
import pygame
from pygame.locals import QUIT, Rect, KEYDOWN, K_SPACE

pygame.init()
pygame.key.set_repeat(5,5)
SURFACE = pygame.display.set_mode((800,600))
FPSCLOCK = pygame.time.Clock()

def main():
    """ main routine """
    walls = 80;
    ship_y = 250
    velocity = 0
    score = 0
    slope = randint(1,6)
    sysfont = pygame.font.SysFont(None,36)
    ship_image = pygame.image.load("ship.png")
    bang_image = pygame.image.load("bang.png")

    # 洞窟の作成
    holes = []  # リスト作成
    for xpos in range(walls): # 0～walls-1まで繰り返し
        holes.append(Rect(xpos * 10, 100,10,400)) # リストに四角形を追加
    game_over = False

    while True:
        is_space_down = False

        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == KEYDOWN:
                if event.key == K_SPACE:
                    is_space_down = True

        if not game_over:
            score += 10
            velocity += -1 if is_space_down else 1 # Trueなら-1　Falseなら1
            ship_y += velocity

            edge = holes[-1].copy() # リストの最後をコピー
            test = edge.move(0,slope)
            if test.top <= 0 or test.bottom >= 600:
                slope = randint(1,6) * (-1 if slope > 0 else 1)
                edge.inflate_ip(0,-20)
            edge.move_ip(10,slope)
            holes.append(edge) # リストに追加
            del holes[0]
            holes = [x.move(-10,0) for x in holes]
            if holes[0].top > ship_y or holes[0].bottom < ship_y + 80:
                game_over = True
        
        # 描画処理
        SURFACE.fill((0,255,0)) # 緑色で塗りつぶし R:0 G:255 B:0
        for hole in holes: # リストの最初から最後まで繰り返し
            pygame.draw.rect(SURFACE, (0,0,0), hole) # 四角形を描画
        SURFACE.blit(ship_image,(0,ship_y)) # プレイヤーを描画
        score_image = sysfont.render("score is {}".format(score),True,(0,0,255))
        SURFACE.blit(score_image, (600,20)) # スコアを描画

        if game_over:
            SURFACE.blit(bang_image, (0,ship_y - 40))

        pygame.display.update()
        FPSCLOCK.tick(15)

if __name__ == '__main__':
    main()
    
