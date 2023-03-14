#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>

/*
functie pentru adaugarea unui element la finalul vectorului
*/
int add_last(void **arr, int *len, data_structure *data)
{
	/*
	-daca vectorul arr e null:
	-se aloca memorie pentru noul element;
	-se adauga in vector cu ajutorul functiei memmove;
	-se creste lungimea in octeti vectorului de octeti;
	*/
	if (*len == 0)
	{
		*arr = malloc(sizeof(head) + data->header->len);
		memmove(*arr, data->header, sizeof(head));
		memmove(*arr + sizeof(head), data->data, data->header->len);
		*len = *len + sizeof(head) + data->header->len;
		return 0;
	}
	/*
	-daca vectorul nu e null:
	-se realoca memorie pentru noul element;
	-se adauga in vector cu ajutorul functiei memmove;
	-se creste lungimea in octeti vectorului de octeti;
	*/
	*arr = realloc(*arr, *len + sizeof(head) + data->header->len);
	memmove(*arr + *len, data->header, sizeof(head));
	memmove(*arr + *len + sizeof(head), data->data, data->header->len);
	*len = *len + sizeof(head) + data->header->len;
	return 0;
}

/*
functie pentru adaugarea unui element la un anumit index din vector
*/
int add_at(void **arr, int *len, data_structure *data, int index)
{
	/*
	-daca indexul e mai mic decat zero se returneaza eroarea -1;
	*/
	if (index < 0)
		return -1;
	/*
	-se calculeaza nr de elemente ale vectorului;
	*/
	int len3 = 0;
	void *ioana = *arr;
	head *joey = (head *)ioana;
	while (ioana - *arr < *len)
	{
		ioana = ioana + sizeof(head) + joey->len;
		len3++;
		joey = (head *)ioana;
	}
	/*
	-daca indexul e mai mare decat nr de elemente se apeleaza functia add_last;
	*/
	if (index > len3 || *arr == NULL)
	{
		add_last(arr, len, data);
		return 0;
	}
	/*
	-se calculeaza lungimea in octeti a vectorului pana la index;
	*/
	int len1 = 0;
	ioana = *arr;
	joey = (head *)ioana;
	while (index--)
	{
		ioana = ioana + sizeof(head) + joey->len;
		len1 = len1 + sizeof(head) + joey->len;
		joey = (head *)ioana;
	}
	/*
	-se realoca memorie pentru noul element;
	-se adauga in vector cu ajutorul functiei memmove;
	-se creste lungimea in octeti vectorului de octeti;
	*/
	*arr = realloc(*arr, *len + sizeof(head) + data->header->len);
	int len2 = *len - len1;
	memmove(*arr + len1 + sizeof(head) + data->header->len, *arr + len1, len2);
	memmove(*arr + len1, data->header, sizeof(head));
	memmove(*arr + len1 + sizeof(head), data->data, data->header->len);
	*len = *len + sizeof(head) + data->header->len;
	return 0;
}

/*
functie pentru gasirea si afisarea unui element din vector
*/
void find(void *data_block, int len, int index)
{
	/*
	-daca vectorul de octeti e gol se termina functia;
	*/
	if (len == 0)
		return;
	/*
	-daca indexul e mai mic decat zero se termina functia;
	*/
	if (index < 0)
		return;
	/*
	-se calculeaza lungimea in octeti a vectorului pana la index;
	*/
	int len3 = 0;
	void *ioana = data_block;
	head *joey = (head *)ioana;
	while (ioana - data_block < len)
	{
		ioana = ioana + sizeof(head) + joey->len;
		len3++;
		joey = (head *)ioana;
	}
	/*
	-daca indexul e mai mare decat nr de elemente se termina functia;
	*/
	if (index > len3)
		return;
	/*
	-se parcurge vectorul de octeti pana la index
	si se retine header-ul in joey si data in valerie;
	*/
	ioana = data_block;
	void *valerie = ioana + sizeof(head);
	joey = (head *)ioana;
	while (index--)
	{
		ioana = ioana + sizeof(head) + joey->len;
		valerie = ioana + sizeof(head);
		joey = (head *)ioana;
	}
	/*
	-se face afisarea pentru fiecare tip;
	*/
	char *nume1, *nume2;
	if (joey->type == 1)
	{
		printf("Tipul 1\n");
		nume1 = (char *)valerie;
		int8_t nr1 = *(int8_t *)(valerie + strlen(nume1) + 1);
		int8_t nr2 = *(int8_t *)(valerie + strlen(nume1) + 1 + 1);
		nume2 = (char *)(valerie + strlen(nume1) + 1 + 1 + 1);
		printf("%s pentru %s\n", nume1, nume2);
		printf("%" PRId8 "\n%" PRId8 "\n\n", nr1, nr2);
	}
	else if (joey->type == 2)
	{
		printf("Tipul 2\n");
		nume1 = (char *)valerie;
		int16_t nr1 = *(int16_t *)(valerie + strlen(nume1) + 1);
		int32_t nr2 = *(int32_t *)(valerie + strlen(nume1) + 1 + 2);
		nume2 = (char *)(valerie + strlen(nume1) + 1 + 2 + 4);
		printf("%s pentru %s\n", nume1, nume2);
		printf("%" PRId16 "\n%" PRId32 "\n\n", nr1, nr2);
	}
	else if (joey->type == 3)
	{
		printf("Tipul 3\n");
		nume1 = (char *)valerie;
		int32_t nr1 = *(int32_t *)(valerie + strlen(nume1) + 1);
		int32_t nr2 = *(int32_t *)(valerie + strlen(nume1) + 1 + 4);
		nume2 = (char *)(valerie + strlen(nume1) + 1 + 4 + 4);
		printf("%s pentru %s\n", nume1, nume2);
		printf("%" PRId32 "\n%" PRId32 "\n\n", nr1, nr2);
	}
}

/*
functie pentru stergerea unui element de la un anumit index din vector
*/
int delete_at(void **arr, int *len, int index)
{
	/*
	-daca lungimea vectorului e 0 se intoarce eroarea -1;
	*/
	if (*len == 0)
		return -1;
	/*
	-se calculeaza lungimea in octeti a vectorului pana la index;
	-se retine head-ul fiecarui element;
	*/
	int len1 = 0;
	void *ioana = *arr;
	head *joey = (head *)ioana;
	while (index--)
	{
		ioana = ioana + sizeof(head) + joey->len;
		len1 = len1 + sizeof(head) + joey->len;
		joey = (head *)ioana;
	}
	/*
	-se sterge elementul de la indexul dat cu ajutorul functiei memmove;
	*/
	int len2 = *len - len1 - joey->len - sizeof(head);
	*len = *len - sizeof(head) - joey->len;
	memmove(*arr + len1, *arr + len1 + sizeof(head) + joey->len, len2);
	*arr = realloc(*arr, *len);
	return 0;
}

/*
functie pentru printarea vectorului
*/
void print(void *arr, int len)
{
	/*
	-daca vectorul de octeti e gol se termina functia;
	*/
	if (len == 0)
		return;
	/*
	-se parcurge vectorul de octeti din element in element si se afiseaza
	pentru fiecare in functie de tip si de tipul datelor;
	*/
	void *ioana = arr;
	void *valerie = ioana + sizeof(head);
	head *joey = (head *)ioana;
	while (ioana - arr < len)
	{
		valerie = ioana + sizeof(head);
		char *nume1, *nume2;
		if (joey->type == 1)
		{
			printf("Tipul 1\n");
			nume1 = (char *)valerie;
			int8_t nr1 = *(int8_t *)(valerie + strlen(nume1) + 1);
			int8_t nr2 = *(int8_t *)(valerie + strlen(nume1) + 1 + 1);
			nume2 = (char *)(valerie + strlen(nume1) + 1 + 1 + 1);
			printf("%s pentru %s\n", nume1, nume2);
			printf("%" PRId8 "\n%" PRId8 "\n\n", nr1, nr2);
		}
		else if (joey->type == 2)
		{
			printf("Tipul 2\n");
			nume1 = (char *)valerie;
			int16_t nr1 = *(int16_t *)(valerie + strlen(nume1) + 1);
			int32_t nr2 = *(int32_t *)(valerie + strlen(nume1) + 1 + 2);
			nume2 = (char *)(valerie + strlen(nume1) + 1 + 2 + 4);
			printf("%s pentru %s\n", nume1, nume2);
			printf("%" PRId16 "\n%" PRId32 "\n\n", nr1, nr2);
		}
		else if (joey->type == 3)
		{
			printf("Tipul 3\n");
			nume1 = (char *)valerie;
			int32_t nr1 = *(int32_t *)(valerie + strlen(nume1) + 1);
			int32_t nr2 = *(int32_t *)(valerie + strlen(nume1) + 1 + 4);
			nume2 = (char *)(valerie + strlen(nume1) + 1 + 4 + 4);
			printf("%s pentru %s\n", nume1, nume2);
			printf("%" PRId32 "\n%" PRId32 "\n\n", nr1, nr2);
		}
		ioana = ioana + sizeof(head) + joey->len;
		joey = (head *)ioana;
	}
}

int main()
{
	// the vector of bytes u have to work with
	// good luck :)
	/*
	-se initializeaza datele;
	*/
	void *arr = NULL;
	int len = 0, len1 = 0, index = 0;
	int8_t number = 0;
	int16_t number2 = 0;
	int32_t number3 = 0;
	char str[256];
	/*
	-se citeste fiecare linie primita de la tastatura intr-un while;
	*/
	while (fgets(str, 256, stdin))
	{
		/*
		-pentru fiecare linie se aloca memorie si se retin datele in structura
		care va fi introdusa in vector conform cerintei;
		-se apeleaza functia aferente fiacarei linii;
		*/
		data_structure *ioana = malloc(sizeof(data_structure));
		char *p = strtok(str, " \n");
		if (p == NULL)
		{
			free(ioana);
			free(arr);
			return 0;
		}
		if (strcmp(p, "insert") == 0)
		{
			p = strtok(NULL, " \n");
			if (strcmp(p, "1") == 0)
			{
				p = strtok(NULL, " \n");
				len1 = strlen(p) + 1;
				ioana->data = malloc(len1);
				memmove(ioana->data, p, len1);
				p = strtok(NULL, " \n");
				len1++;
				ioana->data = realloc(ioana->data, len1);
				number = atoi(p);
				memmove(ioana->data + len1 - 1, &number, 1);
				p = strtok(NULL, " \n");
				len1++;
				ioana->data = realloc(ioana->data, len1);
				number = atoi(p);
				memmove(ioana->data + len1 - 1, &number, 1);
				p = strtok(NULL, " \n");
				len1 += strlen(p) + 1;
				ioana->data = realloc(ioana->data, len1);
				memmove(ioana->data + len1 - strlen(p) - 1, p, strlen(p) + 1);
				ioana->header = malloc(sizeof(head));
				ioana->header->type = 1;
				ioana->header->len = len1;
				add_last(&arr, &len, ioana);
				free(ioana->header);
				free(ioana->data);
			}
			else if (strcmp(p, "2") == 0)
			{
				p = strtok(NULL, " \n");
				len1 = strlen(p) + 1;
				ioana->data = malloc(len1);
				memmove(ioana->data, p, len1);
				p = strtok(NULL, " \n");
				len1 += 2;
				ioana->data = realloc(ioana->data, len1);
				number2 = atoi(p);
				memmove(ioana->data + len1 - 2, &number2, 2);
				p = strtok(NULL, " \n");
				len1 += 4;
				ioana->data = realloc(ioana->data, len1);
				number3 = atoi(p);
				memmove(ioana->data + len1 - 4, &number3, 4);
				p = strtok(NULL, " \n");
				len1 += strlen(p) + 1;
				ioana->data = realloc(ioana->data, len1);
				memmove(ioana->data + len1 - strlen(p) - 1, p, strlen(p) + 1);
				ioana->header = malloc(sizeof(head));
				ioana->header->type = 2;
				ioana->header->len = len1;
				add_last(&arr, &len, ioana);
				free(ioana->header);
				free(ioana->data);
			}
			else if (strcmp(p, "3") == 0)
			{
				p = strtok(NULL, " \n");
				int len1 = strlen(p) + 1;
				ioana->data = malloc(len1);
				memmove(ioana->data, p, len1);
				p = strtok(NULL, " \n");
				len1 += 4;
				ioana->data = realloc(ioana->data, len1);
				number3 = atoi(p);
				memmove(ioana->data + len1 - 4, &number3, 4);
				p = strtok(NULL, " \n");
				len1 += 4;
				ioana->data = realloc(ioana->data, len1);
				number3 = atoi(p);
				memmove(ioana->data + len1 - 4, &number3, 4);
				p = strtok(NULL, " \n");
				len1 += strlen(p) + 1;
				ioana->data = realloc(ioana->data, len1);
				memmove(ioana->data + len1 - strlen(p) - 1, p, strlen(p) + 1);
				ioana->header = malloc(sizeof(head));
				ioana->header->type = 3;
				ioana->header->len = len1;
				add_last(&arr, &len, ioana);
				free(ioana->header);
				free(ioana->data);
			}
		}
		else if (strcmp(p, "insert_at") == 0)
		{
			p = strtok(NULL, " \n");
			index = atoi(p);
			// printf("%d",index);
			p = strtok(NULL, " \n");
			if (strcmp(p, "1") == 0)
			{
				p = strtok(NULL, " \n");
				len1 = strlen(p) + 1;
				ioana->data = malloc(len1);
				memmove(ioana->data, p, len1);
				p = strtok(NULL, " \n");
				len1++;
				ioana->data = realloc(ioana->data, len1);
				number = atoi(p);
				memmove(ioana->data + len1 - 1, &number, 1);
				p = strtok(NULL, " \n");
				len1++;
				ioana->data = realloc(ioana->data, len1);
				number = atoi(p);
				memmove(ioana->data + len1 - 1, &number, 1);
				p = strtok(NULL, " \n");
				len1 += strlen(p) + 1;
				ioana->data = realloc(ioana->data, len1);
				memmove(ioana->data + len1 - strlen(p) - 1, p, strlen(p) + 1);
				ioana->header = malloc(sizeof(head));
				ioana->header->type = 1;
				ioana->header->len = len1;
				add_at(&arr, &len, ioana, index);
				free(ioana->header);
				free(ioana->data);
			}
			else if (strcmp(p, "2") == 0)
			{
				p = strtok(NULL, " \n");
				len1 = strlen(p) + 1;
				ioana->data = malloc(len1);
				memmove(ioana->data, p, len1);
				p = strtok(NULL, " \n");
				len1 += 2;
				ioana->data = realloc(ioana->data, len1);
				number2 = atoi(p);
				memmove(ioana->data + len1 - 2, &number2, 2);
				p = strtok(NULL, " \n");
				len1 += 4;
				ioana->data = realloc(ioana->data, len1);
				number3 = atoi(p);
				memmove(ioana->data + len1 - 4, &number3, 4);
				p = strtok(NULL, " \n");
				len1 += strlen(p) + 1;
				ioana->data = realloc(ioana->data, len1);
				memmove(ioana->data + len1 - strlen(p) - 1, p, strlen(p) + 1);
				ioana->header = malloc(sizeof(head));
				ioana->header->type = 2;
				ioana->header->len = len1;
				add_at(&arr, &len, ioana, index);
				free(ioana->header);
				free(ioana->data);
			}
			else if (strcmp(p, "3") == 0)
			{
				p = strtok(NULL, " \n");
				int len1 = strlen(p) + 1;
				ioana->data = malloc(len1);
				memmove(ioana->data, p, len1);
				p = strtok(NULL, " \n");
				len1 += 4;
				ioana->data = realloc(ioana->data, len1);
				number3 = atoi(p);
				memmove(ioana->data + len1 - 4, &number3, 4);
				p = strtok(NULL, " \n");
				len1 += 4;
				ioana->data = realloc(ioana->data, len1);
				number3 = atoi(p);
				memmove(ioana->data + len1 - 4, &number3, 4);
				p = strtok(NULL, " \n");
				len1 += strlen(p) + 1;
				ioana->data = realloc(ioana->data, len1);
				memmove(ioana->data + len1 - strlen(p) - 1, p, strlen(p) + 1);
				ioana->header = malloc(sizeof(head));
				ioana->header->type = 3;
				ioana->header->len = len1;
				add_at(&arr, &len, ioana, index);
				free(ioana->header);
				free(ioana->data);
			}
		}
		else if (strcmp(p, "delete_at") == 0)
		{
			p = strtok(NULL, " \n");
			index = atoi(p);
			delete_at(&arr, &len, index);
		}
		else if (strcmp(p, "find") == 0)
		{
			p = strtok(NULL, " \n");
			index = atoi(p);
			find(arr, len, index);
		}
		else if (strcmp(p, "print") == 0)
		{
			print(arr, len);
		}
		else if (strcmp(p, "exit") == 0)
		{
			free(ioana);
			free(arr);
			break;
		}
		free(ioana);
	}
	return 0;
}