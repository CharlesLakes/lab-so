import threading

class Lobby:
    def __init__(self):
        self.jugadores = [];
        self.threadLock = threading.Lock()
    
    def entrar(self,jugador):
        self.threadLock.acquire()
        self.jugadores.append({
            "id":jugador,
            "semaphore": threading.Semaphore
        })
        self.threadLock.release()

    