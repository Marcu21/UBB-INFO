package com.example.practic_zboruri;


public class Main {
    public class A {
        private int i = 0; // Variabilă accesibilă în subclase și clase interne

        public class B {
            private int cat;

            public B(int j) {
                i = j; // Acum merge, deoarece i nu mai e privat
            }

            public void impartire() {
                cat = i / 3;
            }

            public int getCat() {
                return cat;
            }
        }
    }
    public static void main(String[] args) {

        HelloApplication.main(args);
    }
}
