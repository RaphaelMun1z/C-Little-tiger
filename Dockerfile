FROM gcc:9.2.0
WORKDIR /code
COPY code/ .
RUN gcc -o app main.c interface/interface.c auth/auth.c db/db.c user/user.c games/bombs/bombs.c games/blaze/blaze.c games/roulette/roulette.c
CMD [ "./app" ]