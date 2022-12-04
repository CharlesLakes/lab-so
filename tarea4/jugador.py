import threading
import random
from datetime import datetime
from lobby import CurrentLobby



class Jugador(threading.Thread):
    def __init__(self, threadID, name, counter):
        super().__init__()
        self.threadID = threadID
        self.name = name
        self.game = random.randint(1,4)
        self.start_time = datetime.now()
        self.counter = counter

    def run(self):
        if self.game == 1:
            game="Partida Estandar"
        elif self.game == 2:
            game="Partida Versus"
        elif self.game == 3:
            game="Partida Rápida"
        elif self.game == 4:
            game="Partida Especial Navidad"
        #self.game = 1
        print(self.name+", "+ str(self.start_time.time())+", "+(game))
        CurrentLobby.entrar(self.threadID,self.game)

        
