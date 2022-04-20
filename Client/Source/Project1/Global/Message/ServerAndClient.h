#pragma once
#include "GameServerMessage.h"
#include "ContentsEnum.h"
#include "ContentsStruct.h"

class ChatMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::string m_NickName;
	std::string m_Chat;
                                                                
public:                                                         
    ChatMessage()                                               
        : GameServerMessage(EMessageType::Chat)                    
        , m_NickName()
        , m_Chat()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~ChatMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_NickName) + DataSizeCheck(m_Chat);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << m_NickName;
        _Serializer << m_Chat;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> m_NickName;
        _Serializer >> m_Chat;

    }                                                           
};                                                              

