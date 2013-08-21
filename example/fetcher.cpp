/**
 * osm-history-fetcher
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <getopt.h>
#include <unistd.h>
#include <iostream>
 
#define OSMIUM_MAIN
#include <osmium.hpp>
#include <fetcher.hpp>

/**
 * entry point into the importer.
 */
int main(int argc, char *argv[]) {
    // local variables for the options/switches on the commandline
    std::string url, statefile;
    bool showHelp = false, printDebugMessages = false;

    // options configuration array for getopt
    static struct option long_options[] = {
        {"help",                no_argument, 0, 'h'},
        {"debug",               no_argument, 0, 'd'},
        {0, 0, 0, 0}
    };

    // walk through the options
    while(1) {
        int c = getopt_long(argc, argv, "hd", long_options, 0);
        if (c == -1)
            break;

        switch (c) {
            // show the help
            case 'h':
                showHelp = true;
                break;

            // enable debug messages
            case 'd':
                printDebugMessages = true;
                break;
        }
    }

    // if help was requested or the filename is missing
    if(showHelp || argc - optind < 2) {
        // print a short description of the possible options
        std::cerr
            << "Usage: " << argv[0] << " URL-TO-REPLICATION STATEFILE" << std::endl
            << "Description: fetches a set of OSM change files from the replication server, optionally simplifies (keep only one version of each item) those changes and spit them into your app via stdout. Maintains a local state file. Without Java. This is mainly a Demo of the fetcher-class to be used in my and your applications." << std::endl
            << "Options: tbd" << std::endl;

        return 1;
    }

    // strip off the filename
    url = argv[optind];
    statefile = argv[optind+1];

    std::cout << "URL=" << url << ", StateFile=" << statefile << std::endl;

    return 0;
}
