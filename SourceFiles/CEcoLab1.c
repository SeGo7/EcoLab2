﻿/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"

#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"


/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ struct IEcoLab1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    } 
	else if ( IsEqualUGUID(riid, &IID_IEcoCalculatorX) ) {
		if (pCMe->m_pInnerUnknown != 0) {
			/* Запрашиваем интерфейс IEcoCalculatorX внутреннего компонента */
			return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
		}
		else {
			*ppv = &pCMe->m_pVTblIEcoCalculatorX;
		}
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
	}
	else if ( IsEqualUGUID(riid, &IID_IEcoCalculatorY) ) {
		*ppv = &pCMe->m_pVTblIEcoCalculatorY;
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        if ( pCMe->m_pInnerUnknown != 0 ) {
            /* Предотвращение рекурсивного вызова */
            if (pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown) == 0) {
                pCMe->m_pInnerUnknown = 0;
            }
            else {
                pCMe->m_cRef = 1;
            }
        }
        if ( pCMe->m_cRef == 0 ) {
            deleteCEcoLab1((IEcoLab1*)pCMe);
        }
        return 0;
    }
    return pCMe->m_cRef;
}

// Функция, меняющая элементы местами
void changeElems(char* el1, char* el2, size_t type_size) {
    size_t i = 0;
    char t;
    for (; i < type_size; ++i) {
        t = el1[i];
        el1[i] = el2[i];
        el2[i] = t;
    }
}

// Stooge sort
int16_t stepStoogeSort(struct IEcoLab1* me, char* start_ptr, size_t l, size_t r, size_t elem_size, int (__cdecl *comp)(const void *, const void*)) 
{
	int third;

	if (comp(start_ptr + l*elem_size, start_ptr + r*elem_size) == 1) changeElems(start_ptr + l*elem_size, start_ptr + r*elem_size, elem_size);

	if (l + 1 >= r) { 
		return 0; 
	}

	third = ((r - l + 1) / 3) ;

	stepStoogeSort(me, start_ptr, l, r - third, elem_size, comp);
	stepStoogeSort(me, start_ptr, l + third, r, elem_size, comp);
	stepStoogeSort(me, start_ptr, l, r - third, elem_size, comp);
}

// Stooge sort
int16_t stoogeSort(struct IEcoLab1* me, char* start_ptr, size_t arr_size, size_t elem_size, int (__cdecl *comp)(const void *, const void*)) 
{
	stepStoogeSort(me, start_ptr, 0, arr_size-1, elem_size, comp);
	
    return 0;
}

// qsort
int16_t ECOCALLMETHOD CEcoLab1_qsort(struct IEcoLab1* me, char* start_ptr, size_t arr_size, size_t elem_size, int (__cdecl *comp)(const void *, const void*)
) {

    CEcoLab1* pCMe = (CEcoLab1*)me;
    int16_t index = 0;

    if (me == 0 || start_ptr == 0 || comp == 0) 
    {
        printf("Pointer error!\n");
        return -1;
    }

	stoogeSort(me, start_ptr, arr_size, elem_size, comp);
    return 0;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_QueryInterface(/* in */ struct IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
		*ppv = &pCMe->m_pVTblIEcoLab1;
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
	else if ( IsEqualUGUID(riid, &IID_IEcoCalculatorX) ) {
        if (pCMe->m_pInnerUnknown != 0) {
            /* Запрашиваем интерфейс IEcoCalculatorX внутреннего компонента */
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
			*ppv = &pCMe->m_pVTblIEcoCalculatorX;
		}
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCalculatorY) ) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        if (pCMe->m_pInnerUnknown != 0) {
            /* Запрашиваем интерфейс IEcoCalculatorX внутреннего компонента */
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
			*ppv = &pCMe->m_pVTblIEcoCalculatorX;
		}
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_AddRef(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_Release(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

	/* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        if ( pCMe->m_pInnerUnknown != 0 ) {
            /* Предотвращение рекурсивного вызова */
            if (pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown) == 0) {
                pCMe->m_pInnerUnknown = 0;
            }
            else {
                pCMe->m_cRef = 1;
            }
        }
        if ( pCMe->m_cRef == 0 ) {
            deleteCEcoLab1((IEcoLab1*)pCMe);
        }
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Addition
 * </сводка>
 *
 * <описание>
 *   Функция Addition для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
int32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_Addition(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

	if (pCMe->m_pIX != 0) {
		result = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, a, b);
	}

    return result;
}

/*
 *
 * <сводка>
 *   Функция Subtraction
 * </сводка>
 *
 * <описание>
 *   Функция Subtraction для интерфейса IEcoCalculatorX
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorX_Subtraction(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoLab1*));
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIX != 0) {
		result = pCMe->m_pIX->pVTbl->Subtraction(pCMe->m_pIX, a, b);
	}

    return result;
}


/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_QueryInterface(/* in */ struct IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoCalculatorX*) - sizeof(struct IEcoLab1*));
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
		*ppv = &pCMe->m_pVTblIEcoLab1;
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
	else if ( IsEqualUGUID(riid, &IID_IEcoCalculatorX) ) {
        if (pCMe->m_pInnerUnknown != 0) {
            /* Запрашиваем интерфейс IEcoCalculatorX внутреннего компонента */
            return pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
        }
        else {
			*ppv = &pCMe->m_pVTblIEcoCalculatorX;
		}
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCalculatorY) ) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoCalculatorY;
		pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_AddRef(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoCalculatorX*) - sizeof(struct IEcoLab1*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_Release(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoCalculatorX*) - sizeof(struct IEcoLab1*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

	/* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        if ( pCMe->m_pInnerUnknown != 0 ) {
            /* Предотвращение рекурсивного вызова */
            if (pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown) == 0) {
                pCMe->m_pInnerUnknown = 0;
            }
            else {
                pCMe->m_cRef = 1;
            }
        }
        if ( pCMe->m_cRef == 0 ) {
            deleteCEcoLab1((IEcoLab1*)pCMe);
        }
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Multiplication
 * </сводка>
 *
 * <описание>
 *   Функция Multiplication для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
int32_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_Multiplication(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
	CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoCalculatorX*) - sizeof(struct IEcoLab1*));
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

	if (pCMe->m_pIY != 0) {
		result = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, a, b);
	}

    return result;
}

/*
 *
 * <сводка>
 *   Функция Division
 * </сводка>
 *
 * <описание>
 *   Функция Division для интерфейса IEcoCalculatorY
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_IEcoCalculatorY_Division(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)((uint64_t)me - sizeof(struct IEcoCalculatorX*) - sizeof(struct IEcoLab1*));
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIY != 0) {
		result = pCMe->m_pIY->pVTbl->Division(pCMe->m_pIY, a, b);
	}

    return result;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab1(struct IEcoLab1* me,  struct IEcoUnknown *pIUnkSystem) {
    IEcoLab1* pCMe = (IEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;
	IEcoUnknown* pOutUnk = (IEcoUnknown*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

	/* Получение интерфейса по работе с умножением и делением у компонента "E" агрегирующего компонент "B" */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIY);
    if (result == 0 && pCMe->m_pIY != 0) {
        /* Получение интерфейса по работе со сложением и вычитанием у компонента "B" */
        result = pCMe->m_pIY->pVTbl->QueryInterface(pCMe->m_pIY, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIX);
        if (result != 0 || pCMe->m_pIX == 0) {
            /* Получение интерфейса по работе со сложением и вычитанием у компонента "A" */
            result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIX);
        }
    }
    else {
        /* Получение интерфейса по работе с умножением и делением у компонента "D" включающего компонент "B" или "A" */
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIY);
        if (result == 0 && pCMe->m_pIY != 0) {
            /* Получение интерфейса по работе со сложением и вычитанием у компонента "B" или "A" */
            result = pCMe->m_pIY->pVTbl->QueryInterface(pCMe->m_pIY, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIX);
        }
        else {
			/* Получение интерфейса по работе со сложением и вычитанием у компонента "B" c поддержкой агрегирования */
			result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOutUnk, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknown);
            if (result != 0 || pCMe->m_pInnerUnknown == 0) {
                /* Получение интерфейса по работе со сложением и вычитанием у компонента "A" */
                result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIX);
            }
        }
    }

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);
	
    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_qsort
};

/* Create Virtual Table IEcoCalculatorX */
IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTbl = {
    CEcoLab1_IEcoCalculatorX_QueryInterface,
    CEcoLab1_IEcoCalculatorX_AddRef,
    CEcoLab1_IEcoCalculatorX_Release,
    CEcoLab1_IEcoCalculatorX_Addition,
    CEcoLab1_IEcoCalculatorX_Subtraction
};

/* Create Virtual Table IEcoCalculatorY */
IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTbl = {
    CEcoLab1_IEcoCalculatorY_QueryInterface,
    CEcoLab1_IEcoCalculatorY_AddRef,
    CEcoLab1_IEcoCalculatorY_Release,
    CEcoLab1_IEcoCalculatorY_Multiplication,
    CEcoLab1_IEcoCalculatorY_Division
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
	
    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

	/* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейсов */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;
	pCMe->m_pVTblIEcoCalculatorX = &g_x9322111622484742AE0682819447843DVTbl;
	pCMe->m_pVTblIEcoCalculatorY = &g_xBD6414C29096423EA90C04D77AFD1CADVTbl;

   /* Инициализация данных */
	pCMe->m_pIX = 0;
	pCMe->m_pIY = 0;
	pCMe->m_pInnerUnknown = 0;
    pCMe->m_Name = 0;

    *ppIEcoLab1 = (IEcoLab1*)pCMe; /* Возврат указателя на интерфейс */
    pIBus->pVTbl->Release(pIBus); /* Освобождение */

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}