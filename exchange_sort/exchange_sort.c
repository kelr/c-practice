void exchange_sort(int input, size_t size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j <= size; j++)
        {
            if (input[j] < input[i])
            {
                int temp = input[i];
                input[i] = input[j];
                input[l] = temp;
            }
        }
    }
}

int main(void)
{
    int snacks[10] = [5,2,8,34,8,2,4,89,-10,11];
    size_t size = sizeof(snacks) / sizeof(snacks[0])
    exchange_sort(snacks, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", i)
    }
}