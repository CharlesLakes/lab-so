import threading
import time

class Partida:
    def __init__(self,capacidad,duracion,jugadores_cola):
        self.jugador_host = -1
        self.capacidad = capacidad
        self.duracion = duracion
        self.jugadores_cola = jugadores_cola
        self.threadLock = threading.Lock()
        self.statusLock = threading.Lock()
        self.queueSemaphore = threading.Semaphore(jugadores_cola)
        self.en_partida = list()
        self.cola = list()

'''Partida Estándar:
    Capacidad de la partida: 15 jugadores
    Duración de la partida: 7 segundos
    Cantidad de jugadores en cola: 7 jugadores'''
class Estandar(Partida):
    def __init__(self):
        super().__init__(15,7,7)

    def in_game(self,jugador,pos):
        self.statusLock.acquire()
        if self.jugador_host == -1:
            self.jugador_host = jugador
        self.statusLock.release()

        if self.jugador_host == jugador:
            time.sleep(self.duracion)
            for j,s in self.en_partida:
                if j != self.jugador_host:
                    s.release()
            self.jugador_host = -1
            self.threadLock.acquire()
            self.en_partida = list()
            if len(self.cola) > 0:
                self.cola[0][1].release()
            self.threadLock.release()
        else:
            self.en_partida[pos][1].acquire()
        print(jugador,"Saliendo")

    def entrar_en_cola(self,jugador):
        #print(jugador,"Esperando que exista espacio en cola")
        self.queueSemaphore.acquire()
        self.threadLock.acquire()
        semaphore = threading.Semaphore(0)
        self.cola.append((jugador,semaphore))
        print(jugador,"Ingresando a la cola")
        while len(self.en_partida) >= self.capacidad or self.cola[0][0] != jugador:
            self.threadLock.release()
            semaphore.acquire()
            self.threadLock.acquire()
        self.cola.pop(0)
        pos = len(self.en_partida)
        self.en_partida.append((jugador,semaphore))
        if len(self.cola) > 0:
            self.cola[0][1].release()
        self.threadLock.release()
        self.queueSemaphore.release()
        print(jugador,"Entrando a partida")
        self.in_game(jugador,pos)

'''Partida Versus:
    Capacidad de la partida: 2 jugadores
    Duración de la partida: 3 segundos
    Cantidad de jugadores en cola: 4 jugadores'''
class Versus(Partida):
    def __init__(self):
        super().__init__(2,3,4)

    def in_game(self,jugador,pos):
        self.statusLock.acquire()
        if self.jugador_host == -1:
            self.jugador_host = jugador
        self.statusLock.release()

        if self.jugador_host == jugador:
            time.sleep(self.duracion)
            for j,s in self.en_partida:
                if j != self.jugador_host:
                    s.release()
            self.jugador_host = -1
            self.threadLock.acquire()
            self.en_partida = list()
            if len(self.cola) > 0:
                self.cola[0][1].release()
            self.threadLock.release()
        else:
            self.en_partida[pos][1].acquire()
        print(jugador,"Saliendo")

    def entrar_en_cola(self,jugador):
        #print(jugador,"Esperando que exista espacio en cola")
        self.queueSemaphore.acquire()
        self.threadLock.acquire()
        semaphore = threading.Semaphore(0)
        self.cola.append((jugador,semaphore))
        print(jugador,"Ingresando a la cola")
        while len(self.en_partida) >= self.capacidad or self.cola[0][0] != jugador:
            self.threadLock.release()
            semaphore.acquire()
            self.threadLock.acquire()
        self.cola.pop(0)
        pos = len(self.en_partida)
        self.en_partida.append((jugador,semaphore))
        if len(self.cola) > 0:
            self.cola[0][1].release()
        self.threadLock.release()
        self.queueSemaphore.release()
        print(jugador,"Entrando a partida")
        self.in_game(jugador,pos)

'''Partida Rápida:
    Capacidad de la partida: 10 jugadores
    Duración de la partida: 6 segundos
    Cantidad de jugadores en cola: 8 jugadores'''

class Rapida(Partida):
    def __init__(self):
        super().__init__(10,6,8)

    def in_game(self,jugador,pos):
        self.statusLock.acquire()
        if self.jugador_host == -1:
            self.jugador_host = jugador
        self.statusLock.release()

        if self.jugador_host == jugador:
            time.sleep(self.duracion)
            for j,s in self.en_partida:
                if j != self.jugador_host:
                    s.release()
            self.jugador_host = -1
            self.threadLock.acquire()
            self.en_partida = list()
            if len(self.cola) > 0:
                self.cola[0][1].release()
            self.threadLock.release()
        else:
            self.en_partida[pos][1].acquire()
        print(jugador,"Saliendo")

    def entrar_en_cola(self,jugador):
        #print(jugador,"Esperando que exista espacio en cola")
        self.queueSemaphore.acquire()
        self.threadLock.acquire()
        semaphore = threading.Semaphore(0)
        self.cola.append((jugador,semaphore))
        print(jugador,"Ingresando a la cola")
        while len(self.en_partida) >= self.capacidad or self.cola[0][0] != jugador:
            self.threadLock.release()
            semaphore.acquire()
            self.threadLock.acquire()
        self.cola.pop(0)
        pos = len(self.en_partida)
        self.en_partida.append((jugador,semaphore))
        if len(self.cola) > 0:
            self.cola[0][1].release()
        self.threadLock.release()
        self.queueSemaphore.release()
        print(jugador,"Entrando a partida")
        self.in_game(jugador,pos)

'''
Partida Especial Navidad:
    Capacidad de la partida: 12 jugadores
    Duración de la partida: 5 segundos
    Cantidad de jugadores en espera o en cola: 10 jugadores'''

class Navidad(Partida):
    def __init__(self):
        super().__init__(12,5,10)

    def in_game(self,jugador,pos):
        self.statusLock.acquire()
        if self.jugador_host == -1:
            self.jugador_host = jugador
        self.statusLock.release()

        if self.jugador_host == jugador:
            time.sleep(self.duracion)
            for j,s in self.en_partida:
                if j != self.jugador_host:
                    s.release()
            self.jugador_host = -1
            self.threadLock.acquire()
            self.en_partida = list()
            if len(self.cola) > 0:
                self.cola[0][1].release()
            self.threadLock.release()
        else:
            self.en_partida[pos][1].acquire()
        print(jugador,"Saliendo")

    def entrar_en_cola(self,jugador):
        #print(jugador,"Esperando que exista espacio en cola")
        self.queueSemaphore.acquire()
        self.threadLock.acquire()
        semaphore = threading.Semaphore(0)
        self.cola.append((jugador,semaphore))
        print(jugador,"Ingresando a la cola")
        while len(self.en_partida) >= self.capacidad or self.cola[0][0] != jugador:
            self.threadLock.release()
            semaphore.acquire()
            self.threadLock.acquire()
        self.cola.pop(0)
        pos = len(self.en_partida)
        self.en_partida.append((jugador,semaphore))
        if len(self.cola) > 0:
            self.cola[0][1].release()
        self.threadLock.release()
        self.queueSemaphore.release()
        print(jugador,"Entrando a partida")
        self.in_game(jugador,pos)
