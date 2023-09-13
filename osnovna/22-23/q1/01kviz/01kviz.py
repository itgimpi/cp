p1 = int (input()) # Алисина (A) предност из прве игре
p2 = int (input()) # Бобанова (B) предност из друге игре
p3 = int (input()) # број Алисиних поена у трећој игри

# u prvoj igri je igrač A bolji za p1 poena
# posle prve igre, igrač A je bolji za p1 poena, razlika je p1

# u drugoj igri je igrač A gori za p2 poena
# posle druge igre, razlika je p1 - p2 poena, ne zna se ko ima više poena, zna se samo razlika

# u trećoj igri je igrač A osvaja p3 poena, B još nije igrao
# razlika A i B je p1 - p2 + p3
# da bi B izjednačio, treba da osvoji tačno p1 - p2 + p3 poena
# da bi B pobedio sa najmanje poena, treba da osvoji tačno 1 poen više od toga

print(p1 - p2 + p3 + 1)