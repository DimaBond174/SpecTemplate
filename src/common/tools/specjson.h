/*
 * This is the source code of SpecNet project
 * It is licensed under MIT License.
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: bondarenkoda@gmail.com
 */

#ifndef SPECJSON_H
#define SPECJSON_H
#include <string.h>
#include <string>

 //must be greater 4:
const int kSPECJSON_LEAF_SIZE = 256;

class  TNode {
public:	
	const char  *pKey;
	unsigned int  lenKey;
	void  *pData;
	unsigned int  lenData;
	TNode  *nextNode;
  char  type;
};

class  TLeaf {
public:
	TNode  nodes[kSPECJSON_LEAF_SIZE];
};

struct WhiteSpaces
{
	unsigned char  t[256];
  WhiteSpaces()
  {
    memset(t,  0,  256);
		//'\t'==ch || ' '==ch || '\n'==ch || '\r'==ch
		t[static_cast<unsigned char>('\t')] = 1;
		t[static_cast<unsigned char>(' ')] = 1;
		t[static_cast<unsigned char>('\n')] = 1;
		t[static_cast<unsigned char>('\r')] = 1;
	}
};
static WhiteSpaces  whiteSpaces;

//static const unsigned char  whitespaces[256]  =  {
// // 0    1    2    3    4    5    6    7      8    9    A    B    C    D    E    F
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   1,   1,   0,   0,   1,   0,   0, // 0
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 1
//   1,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   1,   0,   0,   0, // 2
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 3
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 4
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 5
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 6
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 7
//
// // 128-255
//   0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0
//};

struct Digits
{
	unsigned char  t[256];
  Digits()
  {
		memset(t, 0, 256);
		//'\t'==ch || ' '==ch || '\n'==ch || '\r'==ch
		t[static_cast<unsigned char>('0')] = 1;
		t[static_cast<unsigned char>('1')] = 1;
		t[static_cast<unsigned char>('2')] = 1;
		t[static_cast<unsigned char>('3')] = 1;
		t[static_cast<unsigned char>('4')] = 1;
		t[static_cast<unsigned char>('5')] = 1;
		t[static_cast<unsigned char>('6')] = 1;
		t[static_cast<unsigned char>('7')] = 1;
		t[static_cast<unsigned char>('8')] = 1;
		t[static_cast<unsigned char>('9')] = 1;
		t[static_cast<unsigned char>('.')] = 1;
	}
};
static Digits  digits;

//static const unsigned char  digits[256]  =  {
// // 0    1    2    3    4    5    6    7      8    9    A    B    C    D    E    F
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 0
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 1
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   1,   0, // 2
//   1,   1,   1,   1,   1,   1,   1,   1,     1,   1,   0,   0,   0,   0,   0,   0, // 3
//   0,   0,   0,   0,   0,   1,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 4
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 5
//   0,   0,   0,   0,   0,   1,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 6
//   0,   0,   0,   0,   0,   0,   0,   0,     0,   0,   0,   0,   0,   0,   0,   0, // 7
//
// // 128-255
//   0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,
//   0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0
//};

// 'z' = zero, not a node
// 'n' = next leaf pointer
// 's' = string
// 'a' = array
// 'o' = object
// 'd' = digit
// 'l'  = true, false, null.
class  SpecJson
{
public:
	SpecJson(const char  *json, int  len, bool  doCopy) : _json_len(len) {
		if (doCopy) {
			_jsonCopy = std::string(json, len);
			_json = _jsonCopy.c_str();
		}
		else {
			_json = json;
		}
		state = 0;
		curLeaf = &headLeaf;
		curNode = 0;
		headLeaf.nodes[maxNode].type = 'z';
	}

	~SpecJson() {
		if ('n' == headLeaf.nodes[maxNode].type) {
			freeLeafs((TLeaf *)(headLeaf.nodes[maxNode].pData));
		}
	}

	bool  parse() {
		const char  *p = _json;
		const char  *pEnd = _json + _json_len;
		for (; p < pEnd; ++p) {
			if ('{' == *p) {
				++p;
				if (parseObject_inJSON(p, pEnd)) {
					if (-1 != state) { state = 1; }
					return true;
				}
			}
		}
		return false;
	}

	std::string  getStrByKey(const char  *key, unsigned int  keyLen) {
		return  getStrByKey(key, keyLen, &(headLeaf.nodes[0]));
	}

	inline bool  keyCompare(const char  *lKey, unsigned int  lKeyLen,
		const char  *rKey, unsigned int  rKeyLen) {
		if (lKeyLen == rKeyLen && rKeyLen > 0) {
			do {
				--rKeyLen;
				if (lKey[rKeyLen] != rKey[rKeyLen]) { return false; }
			} while (rKeyLen > 0);
			return  true;
		}
		return  false;
	}

	std::string  getStrByKey(const char  *key, unsigned int  keyLen,
		TNode  *jsonObj) {
		std::string  re;
		if (1 == state) {
			TNode  *cur = jsonObj;
			while (cur) {
				if (keyCompare(key, keyLen, cur->pKey, cur->lenKey)) {
					switch (cur->type) {
					case 's':
					case 'd':
						return  std::string(static_cast<const char *>(cur->pData), cur->lenData);
					}
				}
				cur = cur->nextNode;
			}
		}
		return re;
	}

	TNode * getObjByKey(const char  *key, unsigned int  keyLen,
		TNode  *jsonObj) {
		TNode  *re = 0;
		if (1 == state) {
			TNode  *cur = jsonObj;
			while (cur) {
				if (keyCompare(key, keyLen, cur->pKey, cur->lenKey)) {
					if ('o' == cur->type) {
						re = cur;
						break;
					}
				}
				cur = cur->nextNode;
			}
		}
		return  re;
	}

	TNode * getFirstNode() {
		TNode  *re = 0;
		if (1 == state) {
			re = &(headLeaf.nodes[0]);
			if ('z' == re->type) {
				re = 0;
			}
		} // state
		return re;
	}

private:
	const char  *_json;
  const unsigned int  _json_len;
	std::string  _jsonCopy;
	int  state;
	TLeaf  headLeaf;
	TLeaf  *curLeaf;
	unsigned int  curNode;
	static const unsigned int  maxNode = (kSPECJSON_LEAF_SIZE - 1);

	void  freeLeafs(TLeaf  *n) {
		if ('n' == n->nodes[maxNode].type) {
			freeLeafs(static_cast<TLeaf *>(n->nodes[maxNode].pData));
		}
		delete n;
	}

	TNode * getNewNode() {
		TNode  *re = &(curLeaf->nodes[curNode]);
		re->type = 'z';
		re->lenData = re->lenKey = 0;
		re->pKey = 0;
		re->pData = 0;
		re->nextNode = 0;
		++curNode;
		if (curNode == maxNode) {
			TLeaf  *nextLeaf = new TLeaf();
			nextLeaf->nodes[maxNode].type = 'z';
			TNode  *n = &(curLeaf->nodes[curNode]);
			n->type = 'n';
			n->pData = reinterpret_cast<void *>(nextLeaf);
			n->lenData = n->lenKey = 0;
			n->pKey = 0;
			n->nextNode = 0;
			curLeaf = nextLeaf;
			curNode = 0;
		}
		return re;
	}

	inline unsigned int  getStrLen(const char * &p, const char  *pEnd) {
		unsigned int  re = 0;
		while (p < pEnd) {
			if ('\\' == *p  &&  '"' == *(p + 1)) {
				++re;
				++p;
			}
			else if ('"' == *(p)) {
				return re;
			}
			++re;
			++p;
		}  //  while
		state = -1;
		return  0;
	}

	inline unsigned int  getNumLen(const char * &p, const char  *pEnd) {
		unsigned int  re = 0;
		while (p < pEnd  &&  digits.t[static_cast<unsigned char>(*p)]) {
			++re;
			++p;
		}
		return re;
	}

	TNode * parseArray(const char * &p, const char  *pEnd, unsigned int  *lenData) {
		*lenData = 0;
		TNode  *reNode = 0;
		TNode  *preNode = 0;
		TNode  *curNode = 0;
		unsigned int cnt = 0;

		while (p < pEnd) {
			if (whiteSpaces.t[static_cast<unsigned char>(*p)]) {
				++p;
				continue;
			}
			switch (*p) {
			case ',':
				break;

			case ']':		
				break;
			case '"':        
				curNode = getNewNode();
				++cnt;
				if (preNode) {
					preNode->nextNode = curNode;
					preNode = curNode;
				}
				else {
					reNode = preNode = curNode;
				}
				++p;
				curNode->pData = (void *)(p);
				curNode->lenData = getStrLen(p, pEnd);
				curNode->type = 's'; //string
				break;
			case '{':
				curNode = getNewNode();
				++cnt;
				if (preNode) {
					preNode->nextNode = curNode;
					preNode = curNode;
				}
				else {
					reNode = preNode = curNode;
				}
				curNode->pData = parseObject_inJSON(++p, pEnd);//parseObject_inArray(++p, pEnd);
				curNode->lenData = 0;
				curNode->type = 'o'; //object
				break;
			case '[':
				curNode = getNewNode();
				++cnt;
				if (preNode) {
					preNode->nextNode = curNode;
					preNode = curNode;
				}
				else {
					reNode = preNode = curNode;
				}
				curNode->pData = parseArray(++p, pEnd, &(curNode->lenData));
				curNode->type = 'a'; //array
				break;
			default:
				if (digits.t[static_cast<unsigned char>(*p)]) {
					curNode = getNewNode();
					++cnt;
					if (preNode) {
						preNode->nextNode = curNode;
						preNode = curNode;
					}
					else {
						reNode = preNode = curNode;
					}
					curNode->pData = (void *)(p);
					curNode->lenData = getNumLen(p, pEnd);
					curNode->type = 'd'; //digital
					break;
				}
				return nullptr;
			}
      if (']' == *p)
      {   
        ++p;
        *lenData = cnt;
        return  reNode;
      }
			++p;
		}  //  while (p<pEnd)

		state = -1;
		return nullptr;
	} // parseArray

  TNode * parseObject_inJSON(const char * &p, const char  *pEnd)
  {
    TNode  *reNode = 0;
    TNode  *preNode = 0;
    TNode  *curNode = 0;
    unsigned char  searchLvl = 0; //key
                                  //bool allOk = true;
    while (p < pEnd) {
      if (whiteSpaces.t[static_cast<unsigned char>(*p)]) {
        ++p;
        continue;
      }
      switch (*p) {
      case '"':
        if (0 == searchLvl) {
          curNode = getNewNode();
          curNode->pKey = ++p;
          curNode->lenKey = getStrLen(p, pEnd);
          if (-1 == state) { return nullptr; }
          curNode->type = 'z'; //zero
          if (preNode) {
            preNode->nextNode = curNode;
            preNode = curNode;
          } else {
            reNode = preNode = curNode;
          }
          ++searchLvl;
        } else if (2 == searchLvl) {
          ++p;
          curNode->pData = (void *)(p);
          curNode->lenData = getStrLen(p, pEnd);
          curNode->type = 's'; //string
          searchLvl = 0;
        }
        break;
      case ':':
        if (1 == searchLvl) {
          ++searchLvl;
        } else {
          state = -1;
          return nullptr;
        }
        break;
      case '}':   
        break;
      case '{':
        if (2 == searchLvl) {
          curNode->pData = parseObject_inJSON(++p, pEnd);
          curNode->lenData = 0;
          curNode->type = 'o'; //object
          searchLvl = 0;
        } else {
          state = -1;
          return nullptr;
        }
        break;
      case '[':
        if (2 == searchLvl) {
          curNode->pData = parseArray(++p, pEnd, &(curNode->lenData));
          curNode->type = 'a'; //array
          searchLvl = 0;
        } else {
          state = -1;
          return nullptr;
        }
        break; 
      case ',':
        if (0 == searchLvl)
        {
          break;
        }        
      default:
        if (2 == searchLvl) {
          if (digits.t[static_cast<unsigned char>(*p)]) {
            curNode->pData = (void *)(p);
            curNode->lenData = getNumLen(p, pEnd);
            curNode->type = 'd'; //digital
            searchLvl = 0;
            break;
          }
        } 
        return nullptr;
      }
      if ('}' == *p)
      {
        if (0 == searchLvl)
        {
          ++p;
          return  reNode;
        } else {
          state = -1;
          return nullptr;
        }
      }
      ++p;
    }  //  while (p<pEnd)
    //if (0 == searchLvl
    //  && (p == pEnd)
    //  && ('}' == *(p - 1))) {
    //  return  reNode;
    //}
    state = -1;
    return nullptr;
  }  //  parseObject

};

#endif // SPECJSON_H

