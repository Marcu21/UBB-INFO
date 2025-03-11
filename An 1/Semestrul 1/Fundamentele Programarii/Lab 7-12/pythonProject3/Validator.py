class ValidatorFilm:
    def valideaza_film(self, film):
        erori = ""
        if int(film.get_id_film())<0:
            erori += "id invalid!\n"
        if film.get_titlu() == "":
            erori += "titlu invalid!\n"
        if film.get_descriere() == "":
            erori += "descriere invalida!\n"
        if film.get_gen() == "":
            erori += "gen invalid!\n"
        if len(erori) > 0:
            raise Exception(erori)


class ValidatorClienti:
    def valideaza_client(self, client):
        erori = ""
        if int(client.get_id_client())<0:
            erori += "id invalid!\n"
        if client.get_nume() == "":
            erori += "nume invalid!\n"
        if client.get_prenume() == "":
            erori += "prenume invalid!\n"
        if int(len(client.get_cnp())) != 13:
            erori += "cnp invalid!\n"
        if len(erori) > 0:
            raise Exception(erori)



