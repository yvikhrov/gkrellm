#include <curl/curl.h>
#include "NetworkModule.hpp"
#include <sstream>
#include <net/route.h>
#include <net/if.h>
#include <sys/sysctl.h>

NetMonitorModule::NetMonitorModule()
    : IMonitorModule()
    , m_modName("Network module")
    , m_modData() {
    m_modData.resize(2);
}

NetMonitorModule::~NetMonitorModule() {
}

std::vector<std::string> const& NetMonitorModule::GetData() const {
    return m_modData;
}

std::string const& NetMonitorModule::GetName() const {
    return m_modName;
}

void NetMonitorModule::UpdateData() {
    int m[6];
    char *lim;
    char *next;
    size_t len;
    struct if_msghdr *ifmsg;
    long int ipacks = 0;
    long int opacks = 0;
    long int ibts = 0;
    long int obts = 0;

    m[0] = CTL_NET;
    m[1] = PF_ROUTE;
    m[2] = 0;
    m[3] = 0;
    m[4] = NET_RT_IFLIST2;
    m[5] = 0;
    sysctl(m, 6, NULL, &len, NULL, 0);
    char buf[len];
    sysctl(m, 6, buf, &len, NULL, 0);
    lim = buf + len;
    for (next = buf; next < lim; ) {
        ifmsg = reinterpret_cast<if_msghdr*>(next);
        next += ifmsg->ifm_msglen;

        if (ifmsg->ifm_type == RTM_IFINFO2) {
            struct if_msghdr2 *ifmsg2 = reinterpret_cast<if_msghdr2*>(ifmsg);

            if(ifmsg2->ifm_data.ifi_type!=18) {
                opacks += ifmsg2->ifm_data.ifi_opackets;
                ipacks += ifmsg2->ifm_data.ifi_ipackets;
                obts   += ifmsg2->ifm_data.ifi_obytes;
                ibts   += ifmsg2->ifm_data.ifi_ibytes;
            }
        }
    }
    std::stringstream strs;
    strs << "packets in: " << ipacks;
    strs << " / packets out: " << opacks;
    m_modData[0] = strs.str();
    strs.str(std::string());
    strs.precision(2);
    strs.setf(std::ios::fixed);
    strs << "data resived: " << static_cast<double>(ibts) / 1024 / 1024 / 1024;
    strs << " GB / data sent: " << static_cast<double>(obts) / 1024 / 1024 / 1024;
    strs << " GB";
    m_modData[1] = strs.str();
}
