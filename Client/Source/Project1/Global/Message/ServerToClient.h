#pragma once
#include "GameServerMessage.h"
#include "ContentsEnum.h"

class SignInResultMessage : public GameServerMessage                    
{                                                               
public:                                                         
	ESignInResultType m_SignInResultType;
                                                                
public:                                                         
    SignInResultMessage()                                               
        : GameServerMessage(EMessageType::SignInResult)                    
        , m_SignInResultType()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SignInResultMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_SignInResultType);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer<<static_cast<int>(m_SignInResultType);

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        int temp ;		
        _Serializer>>temp;
        m_SignInResultType = static_cast<ESignInResultType>(temp); 

    }                                                           
};                                                              

class ServerDestroyMessage : public GameServerMessage                    
{                                                               
public:                                                         
                                                                
public:                                                         
    ServerDestroyMessage()                                               
        : GameServerMessage(EMessageType::ServerDestroy)                    
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~ServerDestroyMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return 0;    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            

    }                                                           
};                                                              

class SignUpResultMessage : public GameServerMessage                    
{                                                               
public:                                                         
	ESignUpResultType m_SignUpResultType;
                                                                
public:                                                         
    SignUpResultMessage()                                               
        : GameServerMessage(EMessageType::SignUpResult)                    
        , m_SignUpResultType()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SignUpResultMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_SignUpResultType);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer<<static_cast<int>(m_SignUpResultType);

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        int temp ;		
        _Serializer>>temp;
        m_SignUpResultType = static_cast<ESignUpResultType>(temp); 

    }                                                           
};                                                              

