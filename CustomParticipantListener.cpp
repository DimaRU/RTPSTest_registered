//
//  CustomParticipantListener.cpp
//  TestFastRTPS
//
//  Created by Dmitriy Borovikov on 29/07/2019.
//  Copyright © 2019 Dmitriy Borovikov. All rights reserved.
//

#include "CustomParticipantListener.h"
#include <arpa/inet.h>
#include <fastrtps/rtps/common/Locator.h>

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

void CustomParticipantListener::onReaderDiscovery(RTPSParticipant *participant, ReaderDiscoveryInfo &&info)
{
    (void)participant;
    switch(info.status) {
        case ReaderDiscoveryInfo::DISCOVERED_READER:
            std::cout << "Reader for topic '" << info.info.topicName() << "' type '" << info.info.typeName() << "' discovered" << std::endl;
            DumpLocators(info.info.remote_locators().unicast);
             break;
        case ReaderDiscoveryInfo::CHANGED_QOS_READER:
            break;
        case ReaderDiscoveryInfo::REMOVED_READER:
            std::cout << "Reader for topic '" << info.info.topicName() << "' type '" << info.info.typeName() << "' left the domain." << std::endl;
            break;
    }
}

void CustomParticipantListener::onWriterDiscovery(RTPSParticipant *participant, WriterDiscoveryInfo &&info)
{
    (void)participant;
    switch(info.status) {
        case WriterDiscoveryInfo::DISCOVERED_WRITER:
            std::cout << "Writer for topic '" << info.info.topicName() << "' type '" << info.info.typeName() << "' discovered" << std::endl;
            DumpLocators(info.info.remote_locators().unicast);
             break;
        case WriterDiscoveryInfo::CHANGED_QOS_WRITER:
            break;
        case WriterDiscoveryInfo::REMOVED_WRITER:
            std::cout << "Writer for topic '" << info.info.topicName() << "' type '" << info.info.typeName() << "' left the domain." << std::endl;
            break;
    }
}

void CustomParticipantListener::onParticipantDiscovery(RTPSParticipant *participant, ParticipantDiscoveryInfo &&info)
{
    (void)participant;
    switch(info.status) {
        case ParticipantDiscoveryInfo::DISCOVERED_PARTICIPANT:
            std::cout << "Participant '" << info.info.m_participantName << "' discovered" << std::endl;
            DumpLocators(info.info.default_locators.unicast);
             break;
        case ParticipantDiscoveryInfo::DROPPED_PARTICIPANT:
            std::cout << "Participant '" << info.info.m_participantName << "' dropped" << std::endl;
            break;
        case ParticipantDiscoveryInfo::REMOVED_PARTICIPANT:
            std::cout << "Participant '" << info.info.m_participantName << "' removed" << std::endl;
            break;
        case ParticipantDiscoveryInfo::CHANGED_QOS_PARTICIPANT:
            break;
    }
}

void CustomParticipantListener::DumpLocators(ResourceLimitedVector<eprosima::fastrtps::rtps::Locator_t> locators)
{
    char addrString[INET6_ADDRSTRLEN+1];

    for (auto locator = locators.cbegin(); locator != locators.cend(); locator++) {
        switch (locator->kind) {
            case LOCATOR_KIND_UDPv4:
                std::cout << inet_ntop(AF_INET, locator->address+12, addrString, sizeof(addrString)) << ":" << locator->port << std::endl;
                break;
            case LOCATOR_KIND_UDPv6:
                std::cout << inet_ntop(AF_INET6, locator->address, addrString, sizeof(addrString)) << ":" << locator->port << std::endl;
                break;
            default:
                break;
        }
    }
}