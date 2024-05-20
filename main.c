#include <stdio.h>
#include <string.h> 
#include <zigbee.pb.h>
#include "pb_common.h"
#include "pb_encode.h"
#include "pb_decode.h"

void print_array(uint8_t *buffer, int n){ 
    printf("\n");
    for (int i = 0; i < 64; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

int main(void) {

    uint8_t buffer[64] = {0};

    Zigbee_t pack = Zigbee_t_init_default;
    pb_ostream_t o_stream  = {0};

    Zigbee_t unpack  = Zigbee_t_init_default;
    pb_istream_t i_stream  = {0};

    o_stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    // into value 
    pack.sync = true;
    pb_encode(&o_stream, Zigbee_t_fields, &pack);
    printf("Buffer after encoder:");
    print_array(buffer, o_stream.bytes_written);
    memset(buffer, 0, sizeof(buffer));


    pack.sw.deviceID = 0xaaaa;
    pack.sw.endpoint = 1;
    pack.sw.status = true;
    pack.has_sw = true;
    pack.sync = false;
    pb_encode(&o_stream, Zigbee_t_fields, &pack);
    printf("Buffer after encoder:");
    print_array(buffer, o_stream.bytes_written);
    memset(buffer, 0, sizeof(buffer));

    pack.sw.status = false;
    pack.sw.endpoint = 2;
    pb_encode(&o_stream, Zigbee_t_fields, &pack);
    printf("Buffer after encoder:");
    print_array(buffer, o_stream.bytes_written);
    memset(buffer, 0, sizeof(buffer));


    pack.sw.status = false;
    pack.sw.endpoint = 3;
    pb_encode(&o_stream, Zigbee_t_fields, &pack);
    printf("Buffer after encoder:");
    print_array(buffer, o_stream.bytes_written);
    memset(buffer, 0, sizeof(buffer));
    uint8_t buffer_decode[] ={ 
	10 ,6 ,8 ,170 ,213 ,2 ,16 ,2
    };
    i_stream = pb_istream_from_buffer(buffer_decode, sizeof(buffer_decode));
    pb_decode(&i_stream, Zigbee_t_fields, &unpack);
    printf("Buffer after decoder:\n");
    printf("Device id: %d\n", unpack.sw.deviceID);
    printf("Endpoint: %ld\n", unpack.sw.endpoint);
    printf("Status: %ld\n", unpack.sw.status);

    printf("Sync: %d\n", unpack.sync);
    return 0;
}
