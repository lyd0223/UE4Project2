#pragma once
#include "GameServerMessage.h"

class ChatMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::string m_ID;
	std::string m_Message;
                                                                
public:                                                         
    ChatMessage()                                               
        : GameServerMessage(EMessageType::Chat)                    
        , m_ID()
        , m_Message()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~ChatMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_ID) + DataSizeCheck(m_Message);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer << m_ID;
        _Serializer << m_Message;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer >> m_ID;
        _Serializer >> m_Message;

    }                                                           
};                                                              

