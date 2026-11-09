#include <nodepp/nodepp.h>
#include <ungine/ungine.h>

/*────────────────────────────────────────────────────────────────────────────*/

using namespace nodepp;

namespace ungine { node_t main() {
return node::node_scene([=]( ptr_t<node_t> self ){

    auto img = texture  ::load( "./test/emoji.png" );
    auto mdl = model    ::load( "./test/map.glb" );
    auto ply = model    ::load( "./test/player.glb" );
    auto ann = animation::load( "./test/player.glb" );

    self->onClose([=](){ 
        texture  ::unload(img); 
        model    ::unload(mdl); 
        model    ::unload(ply); 
        animation::unload(ann);
    });

}); }}

/*────────────────────────────────────────────────────────────────────────────*/

void onMain(){

    ungine::engine::start  ( 800, 600, "MyGame" );
    ungine::engine::set_fps( 60 ); 
    
    ptr_t<ungine::node_t> node (0UL);

    process::add( coroutine::add( COROUTINE(){
    coBegin; coDelay(10); do {
        node[0].free();
        node[0] = ungine::main();
    } while(0); coGoto(0); coFinish }));
    
}

/*────────────────────────────────────────────────────────────────────────────*/