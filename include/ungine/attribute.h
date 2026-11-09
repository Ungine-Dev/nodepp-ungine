/*
 * Copyright 2023 The Ungine Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/UngineOfficial/Ungine/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef UNGINE_ATTRIBUTE
#define UNGINE_ATTRIBUTE

/*────────────────────────────────────────────────────────────────────────────*/

namespace ungine { class attribute_t {
protected: map_t<string_t,any_t> storage; public:    

    attribute_t() noexcept {}

    /*─······································································─*/

    bool has_attribute   ( string_t name ) const noexcept { return storage.has(name); }

    void remove_attribute( string_t name ) const noexcept { storage.erase( name ); }

    template< class T >
    bool has_attribute_as( string_t name ) const noexcept { 
    if( !has_attribute( name ) ){ return false; }
         return sizeof(get_attribute<T>(name)[0])==sizeof(T); 
    }

    /*─······································································─*/

    void set_attribute( string_t name, const char* value ) const noexcept { do {
        if( !has_attribute_as<string_t>( name ) ){ break; }
        get_attribute<string_t>( name )[0] = string_t(value); return;
    } while(0); storage[name]= type::bind( string::to_string( value ) ); }

    template< class T >
    void set_attribute( string_t name, T value ) const noexcept { do {
        if( !has_attribute_as<string_t>( name ) ){ break; }
        get_attribute<T>( name )[0]=value; return;
    } while(0); storage[name]= type::bind( value ); }

    void clear() noexcept { storage.clear(); }

    /*─······································································─*/

    template< class T >
    ptr_t<T> get_attribute( string_t name ) const {
    if( !has_attribute_as   <T>( name ) ){ 
        /*--*/ set_attribute<T>( name, T() );
        return get_attribute<T>( name ); 
    }   return storage[ name ].as<ptr_t<T>>(); }

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif

/*────────────────────────────────────────────────────────────────────────────*/