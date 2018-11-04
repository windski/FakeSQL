//
// Created by yurunyang on 18-9-20.
//

#include <iostream>

#include "bson_.h"

#include <cassert>

using  namespace bson_;
bson_couple::bson_couple()
    : b(NULL), buf(NULL), buflen(0),
      writer(bson_writer_new(&buf, &buflen, 0, bson_realloc_ctx, NULL))
{ }

bson_couple::~bson_couple()
{
    bson_writer_destroy(writer);
    //bson_destroy(b);
    bson_free (buf);
    //bson_destroy_with_steal(b);
}

void bson_couple::insert_UTF8_value
        (std::string attribute, std::string value) {

    //bson_error_t error;
    int result;

    bson_writer_begin (writer, &b);
    result = bson_append_utf8(b,attribute.c_str(),-1,value.c_str(),-1);
    bson_writer_end(writer);

    // 添加失败就崩溃!
    assert(result != 0);

//        if(result== false)
//        {
//            throw false;
//
//        }
//        bson_writer_rollback(writer);
//        std::cout<<error.code<<std::endl;


}

bson_t * bson_couple::get_bson()
{
    return b;
}


void bson_couple::insert_int32_value(std::string attribute, int32_t value) {

    bson_writer_begin (writer, &b);
    int result = bson_append_int32(b,attribute.c_str(),-1,value);
    bson_writer_end(writer);

    // 添加失败就崩溃!
    assert(result != 0);
}

bson_t* bson_couple::rebuildFromBuffer(const uint8_t *buf) {
    bson_reader_t *reader = bson_reader_new_from_data(buf,500);
    char * str;
    const bson_t *bsomTemp_;
    while ((bsomTemp_  = bson_reader_read (reader, NULL))) {
        str = bson_as_canonical_extended_json (bsomTemp_, NULL);
        fprintf (stdout, "%s\n", str);
        bson_free (str);
    }

    /*
     * Cleanup after our reader, which closes the file descriptor.
     */
    bson_reader_destroy (reader);

}


uint8_t* bson_couple::getBsonBuf() {
    return this->buf;
}

size_t bson_couple::getBsonLength() {
    return bson_writer_get_length(writer);
}
