#ifndef NO_SG
#define NO_SG

class No_SG {
  private:
    int valor;
    No_SG *dir, *esq;
  protected:

  public:
    No_SG(int v){
      valor = v;
      dir = esq = NULL;
    }
    ~No_SG(){ }
    void setValor(int v) { valor = v; }
    void setDir(No_SG *d) { dir = d; }
    void setEsq(No_SG *e) { esq = e; }
    int getValor() { return valor; }
    No_SG *getDir() { return dir; }
    No_SG *getEsq() { return esq; }
};

#endif
