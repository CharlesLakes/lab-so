import threading

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
        if game == 1:
            self.pre_estandar.append(jugador)
        elif game == 2:
            self.pre_versus.append(jugador)
        elif game == 3:
            self.pre_rapida.append(jugador)
        elif game == 4:
            self.pre_navidad.append(jugador)
        self.threadLock.release()



