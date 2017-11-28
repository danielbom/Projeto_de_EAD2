#ifndef NO_SG
#define NO_SG

class No_SG {
	private:
		int valor;
		No_SG *dir, *esq, *pai;
	protected:

	public:
		No_SG(){
			valor = 0;
			dir = esq = pai = NULL;
		}

		No_SG(int v){
			valor = v;
			dir = esq = pai = NULL;
		}

		~No_SG(){ }

		void setValor(int v) { valor = v; }
		void setDir(No_SG *d) { dir = d; }
		void setEsq(No_SG *e) { esq = e; }
		void setPai(No_SG *p) { pai = p; }
		int getValor() { return valor; }
		No_SG *getDir() { return dir; }
		No_SG *getEsq() { return esq; }
		No_SG *getPai() { return pai; }
};

#endif
