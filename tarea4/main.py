from jugador import Jugador


def make_files():
    a = [   "PartidaEstandar.txt",
            "PartidaVersus.txt",
            "PartidaRápida.txt",
            "PartidaEspecialNavidad.txt",
            "Salida.txt"]
    for i in a:
        archivo = open(i,"w")
        archivo.close()
    return






def make_threads():
    threads = []
    # Create 120 new threads
    for i in range(32):
        thread = Jugador(i+1, "Jugador"+str(i+1), 1)
        thread.start()
        threads.append(thread)


    # Wait for all threads to complete
    for t in threads:
        t.join()
    print ("Exiting Main Thread")
    return





make_threads()

