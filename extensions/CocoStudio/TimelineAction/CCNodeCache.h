/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_NODE_CACHE_H__
#define __CC_NODE_CACHE_H__

#include "CCTimeLine.h"
#include "../Json/DictionaryHelper.h"

namespace cocos2d
{
	namespace extension
	{
		class WidgetPropertiesReader0300;
	}
}

namespace cocostudio {
namespace animation {


typedef cocos2d::CCNode* (cocos2d::CCObject::*NodeCreateCallback)(const rapidjson::Value& json);
#define NodeCreateCallback_selector(_SELECTOR) (NodeCreateCallback)(&_SELECTOR)

class CC_EX_DLL NodeCreateCallFunc : public cocos2d::CCObject
{
public:
    static NodeCreateCallFunc* create(CCObject* target, NodeCreateCallback callback);

    NodeCreateCallFunc();
    ~NodeCreateCallFunc();
    bool init(CCObject* target, NodeCreateCallback callback);
    cocos2d::CCNode* excute(const rapidjson::Value& json);
    
protected:
    CCObject* _target;
    NodeCreateCallback _callback;
};


class CC_EX_DLL NodeCache : public cocos2d::CCObject
{
public:
    static NodeCache* getInstance();
    static void destroyInstance();

    virtual ~NodeCache();
    void purge();

    void init();

    cocos2d::CCNode* createNode(const std::string& filename);

    cocos2d::CCNode* loadNodeWithFile(const std::string& fileName);
    cocos2d::CCNode* loadNodeWithContent(const std::string& content);
protected:

    cocos2d::CCNode* loadNode(const rapidjson::Value& json);

    void initNode(cocos2d::CCNode* node, const rapidjson::Value& json);

    cocos2d::CCNode* loadSimpleNode(const rapidjson::Value& json);
    cocos2d::CCNode* loadSprite(const rapidjson::Value& json);
    cocos2d::CCNode* loadParticle(const rapidjson::Value& json);
	cocos2d::CCNode* loadWidget(const rapidjson::Value& json);


    cocos2d::CCDictionary* _funcs;  // <std::string, NodeCreateCallFunc*>
    cocos2d::CCDictionary* _nodes;  // <std::string, cocos2d::CCNode*>

	cocos2d::extension::WidgetPropertiesReader0300* _guiReader;
};

}
}


#endif /*__CC_NODE_CACHE_H__*/
