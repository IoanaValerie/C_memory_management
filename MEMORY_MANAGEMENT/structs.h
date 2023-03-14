typedef struct __attribute__((packed)) head
{
	unsigned char type;
	unsigned int len;
} head;

typedef struct data_structure
{
	head *header;
	void *data;
} data_structure;
