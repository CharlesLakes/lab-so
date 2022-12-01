import threading
from partida import *

class Lobby:
    def __init__(self):
        self.jugadores = []
        self.pre_estandar = []
        self.pre_versus = []
        self.pre_rapida = []
        self.pre_navidad = []
        self.threadLock = threading.Lock()
    
    def entrar(self,jugador,game):
        self.threadLock.acquire()
        semaphore = threading.Semaphore(0)
        if game == 1:
            partida = Estandar
            queue = self.pre_estandar
            self.pre_estandar.append((jugador,semaphore))
        elif game == 2:
            partida = Versus
            queue = self.pre_versus
            self.pre_versus.append((jugador,semaphore))
        elif game == 3:
            partida = Rapida
            queue = self.pre_rapida
            self.pre_rapida.append((jugador,semaphore))
        elif game == 4:
            partida = Navidad
            queue = self.pre_navidad
            self.pre_navidad.append((jugador,semaphore))
        print("Entro al lobby")
        while queue[0][0] != jugador and len(partida.cola) >= partida.capacidad:
            self.threadLock.release()
            semaphore.acquire()
            self.threadLock.acquire()
        queue.pop(0)
        self.threadLock.release()

        partida.entrar_en_cola(jugador,queue)


CurrentLobby = Lobby()
        
        
        


