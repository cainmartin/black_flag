#include <engine.h>
#include <stdio.h>

int main(void) {

    printf("Trying to make the donkey fartbox run\n");

    EngineConfig engine_config = { 0 };
    Engine* engine = engine_create(&engine_config);

    while (engine_should_quit(engine))
    {

    }

    engine_shutdown(engine);

    return 0;
}