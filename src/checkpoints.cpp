// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 Krugercoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //

	// no checkpoint now, can be added in later releases
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (  0, uint256("0x1d8ea43e6417420f3caf6adc2a98749746bb6b22e15b0467e873c4549775f01e"))
            ( 543856, uint256("0xe3f64cfb86020e061c2d11bae753914fec3699dfd56a98738a7372ade4ed4c38"))
            ( 980174, uint256("0xedfc1a0e99944b2e38c38a1a889fa1782e2449c9e786914367eae2d273d73273"))
            ( 1119999, uint256("0x3b1bd50a156925d890ac8683edddb8d1aa8fbd57bfd2b27258a46ff17181294c"))
            ( 1120000, uint256("0xf686dffe3bf6baa058b0d606661325dd973b893488719b899fb4f4e8d2599f1f"))
            ( 1121076, uint256("0x1cff96008825bd496c7cbb4760ba1f9d3fa81c675d39cbf54df7dd7ef093d011"))
            ( 1125000, uint256("0x140173a917a105850336ca78efdce0e8217b5cfb619e35cc4998635ab99ce56b"))
            ( 1340000	, uint256("0x64c87d0cd4cced8e6e9eb83b1692f10974151b0c7fad6914d021c3448d966627"))
			;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
		// return true;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
	
        return mapCheckpoints.rbegin()->first;
		// return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
				// return NULL;
        }
        return NULL;
    }
}
