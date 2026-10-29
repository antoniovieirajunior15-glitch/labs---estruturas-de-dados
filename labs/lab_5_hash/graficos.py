import pandas as pd, matplotlib.pyplot as plt
a = pd.read_csv("colisoes_acumuladas.csv")
plt.figure(figsize=(8,5))
for c, l in [("linear","Linear"),("quadratica","Quadrática"),("duplo","Duplo hash")]:
    plt.plot(a.chaves, a[c], label=l)
plt.xlabel("Chaves inseridas"); plt.ylabel("Colisões acumuladas")
plt.title("Chaves inseridas x colisões (M = 1201)"); plt.grid(alpha=.3); plt.legend()
plt.savefig("grafico_colisoes.png", dpi=150, bbox_inches="tight")
 
r = pd.read_csv("resumo.csv")
fig, ax = plt.subplots(1, 2, figsize=(12,5))
for e, g in r.groupby("estrategia"):
    ax[0].plot(g.chaves, g.colisoes, marker="o", label=e)
    ax[1].plot(g.chaves, g.tempo_us, marker="o", label=e)
ax[0].set_title("Colisões"); ax[1].set_title("Tempo de inclusão")
ax[0].set_ylabel("Nº de colisões"); ax[1].set_ylabel("Tempo (µs)")
for x in ax: x.set_xlabel("Chaves na tabela"); x.set_xticks([64,128,256,512,1000]); x.grid(alpha=.3); x.legend()
plt.savefig("grafico_comparativo.png", dpi=150, bbox_inches="tight")