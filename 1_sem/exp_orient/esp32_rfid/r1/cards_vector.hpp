// ----------------------------------------------------------------------------------------------------------
// VETOR PRIMITIVO
// ----------------------------------------------------------------------------------------------------------

#define MAX_CARDS_NUM   6 // sao apenas 6 cartoes (C nao tem vetor, pro vetor crescer precisaria de malloc)
#define SENTINEL_VALUE 0U // acho que nenhum cartao tem UID == 0
#define INVALID_INDEX  -1 // sinaliza falha nos procedimentos de manipulacao do array (error handling)
#define FOR_EACH_CARD(i) for(int i = 0; i < MAX_CARDS_NUM; i++) // syntax sugar pra mim, mesmo

// ----------------------------------------------------------------------------------------------------------

inline int cards_push(unsigned int* arr, unsigned int elem)
{
  FOR_EACH_CARD(i)
  {
    if (arr[i] == SENTINEL_VALUE)
    {
      arr[i] = elem;
      return i;
    }

    if (arr[i] == elem)
    {
      return i;
    }
  }

  return INVALID_INDEX;
}

// ----------------------------------------------------------------------------------------------------------

inline int cards_search(unsigned int* arr, unsigned int elem)
{
  FOR_EACH_CARD(i)
  {
    if (arr[i] == elem)
    {
      return i;
    }
  }

  return INVALID_INDEX;
}

// ----------------------------------------------------------------------------------------------------------

inline int cards_detach(unsigned int* arr, unsigned int elem)
{
  const int foundId = cards_search(arr, elem);
  if (foundId == INVALID_INDEX)
  {
    return INVALID_INDEX;
  }

  const int lastId = MAX_CARDS_NUM - 1;
  if (foundId == lastId)
  {
    arr[foundId] = SENTINEL_VALUE;
    return foundId;
  }

  for (int i = foundId; i < MAX_CARDS_NUM - 1; i++)
  {
    const unsigned int next = arr[i + 1];
    const bool hasNext = next != 0;
    if (!hasNext)
    {
      return foundId;
    }

    arr[i] = next;
    arr[i + 1] = SENTINEL_VALUE;
  }
  
  return INVALID_INDEX;
}

// ----------------------------------------------------------------------------------------------------------

inline void cards_initialize(unsigned int* arr)
{
  FOR_EACH_CARD(i) arr[i] = SENTINEL_VALUE;
}

// ----------------------------------------------------------------------------------------------------------
