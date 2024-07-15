#include "ChannelHandler.h"

#include <GL/freeglut.h>

#include "Tool.h"
#include "Canvas.h"
#include "Channel.h"
#include "Parameter.h"

#include <sys/types.h>
#ifdef __WIN32__
#include <winsock2.h>
#define RECV_FLAGS 0
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#define RECV_FLAGS (MSG_TRUNC | MSG_DONTWAIT)
#endif
#include <strings.h>
#include <iostream>

CChannelHandler::CChannelHandler(CTool* pTool)
{
	m_pTool = pTool;
	for(int i = 0; i < NUMCHANNELS; ++i)
	{
		m_vChannel[i] = new CChannel(m_pTool);
		m_vChannel[i]->setId('0');
	}
	m_vChannel[0]->setColor(1, 0, 0);
	m_vChannel[1]->setColor(0, 1, 0);
	m_vChannel[2]->setColor(0, 1, 1);
	m_vChannel[3]->setColor(1, 1, 0);
	m_vChannel[4]->setColor(1, 0, 1);

	m_pParameter = new CParameter(m_pTool);
	m_pParameter->setId('0');

	m_iPause = 0;
	
	initNet();
}

CChannelHandler::~CChannelHandler(void)
{
}

void CChannelHandler::togglePause()
{
	m_iPause = !m_iPause;
}

void CChannelHandler::setId(unsigned char channel, unsigned char id)
{
	m_vChannel[channel]->setId(id);
}

void CChannelHandler::setParameterId(unsigned char id)
{
	m_pParameter->setId(id);
}

void CChannelHandler::drawGraphs(int width, int height)
{
	for(int i = 0; i < NUMCHANNELS; ++i)
	{
		m_vChannel[i]->drawGraph(width, height);
	}
}

void CChannelHandler::drawChannels(int channelHeight)
{
	for(int i = 0; i < NUMCHANNELS; ++i)
	{
		m_vChannel[i]->drawInfo();
		glTranslatef(0.0f, GLfloat(channelHeight), 0.0f);
	}
}

void CChannelHandler::drawParameter()
{
	m_pParameter->draw();
}

void CChannelHandler::initNet()
{
   struct sockaddr_in servaddr;

   #ifdef _WIN32
   WSADATA wsaData;
   int wsa = WSAStartup(MAKEWORD(2, 2), &wsaData);
   std::cout << "wsa start (channel): " << wsa << std::endl;
   #endif
   
   udpfd = socket(AF_INET, SOCK_DGRAM, 0);
   std::cout << "udpfd (channel): " << udpfd << std::endl;

   #ifdef _WIN32
   u_long mode = 0;
   int ioctl = ioctlsocket(udpfd, FIONBIO, &mode);
   std::cout << "ioctl (channel): " << ioctl << std::endl;
   #endif

   memset(&servaddr, 0, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(1234);

   int bnd = bind(udpfd, (sockaddr*)&servaddr, sizeof(servaddr));
   std::cout << "bnd (channel): " << bnd << std::endl;
}

void CChannelHandler::readRemote()
{
   struct
   {
     uint16_t timer;
     uint8_t channel[6];
     int32_t data[6];
   } datain;

   ssize_t n;

   n = recv(udpfd, (char *)&datain, sizeof(datain), RECV_FLAGS);
   if(n == sizeof(datain))
   {
      m_pTool->remoteTimeTick();
      for(int i = 0; i < 5; ++i)
      {
			setId(i, datain.channel[i]);
         m_vChannel[i]->setValue(datain.data[i]);
      }
      setParameterId(datain.channel[5]);
      m_pParameter->setValue(datain.data[5]);
   }
}

      
