/* main.cpp */

#include <iostream>
#include "export_cfg.hpp"
#include "Feed.hpp"

using namespace std;

int main(int argc, char* argv[])
{
		string feed_url;
		map<string, string> articles;

		// validate arguments
  		if (argc == 2) 
		{
			feed_url = argv[1];
		}
		else
		{
			cerr << "usage: FeedReaderTester.exe <feed_url>\n";
            return 1;
		}

        try
        {
				// init once per process
				FeedReader::Feed::Initialize();

				// create custom feed config with the path of the xsl files
				FeedReader::FeedConfig feedConfig("./xsl");

				// optionally, customize the list of xsl files and feed types 
				// feedConfig.m_feed_types.clear();
				// feedConfig.m_feed_types.push_back(std::make_pair("BroadCatching_02_xsl.txt", "BroadCatching02"));

				// create feed reader
				FeedReader::Feed feedReader(feed_url,feedConfig);
				
				// check feed
				feedReader.CheckFeed();

				// get results
				std::cout << "----------Feed---------" <<endl
					      << "URL: '" << feedReader.GetUrl() << "'" << endl;
				// print channel elements
				for (FeedReader::Feed::feed_element_iterator fitr = feedReader.begin_feed_elements();
					 fitr != feedReader.end_feed_elements(); fitr++)
				{
					// std::cout << fitr->first << ":	'" <<  fitr->second << "'" << endl;
				}
				
				// print item elements
				for (FeedReader::Feed::entry_iterator itr = feedReader.begin_entries();
					 itr != feedReader.end_entries(); itr++)
				{
				std::cout << "afficher un nouvel article" << std::endl;
					// std::cout << "Item ID: '"	<< itr->UniqueId	<< "'" << std::endl
							  // << "IsLive: '"	<< itr->IsLive		<< "'" << std::endl;
					//itr->Print(std::cout);
					for (FeedReader::Entry::entry_element_iterator itr2 = itr->begin_entry_elements(); itr2 != itr->end_entry_elements(); ++itr2) 		{
						articles[itr2->first] = itr2->second;
					}
					for(map<string, string>::iterator it=articles.begin(); it!=articles.end(); ++it)
					{
						cout << it->first << " --- " << it->second << " --- " << endl;
					}
				}
        }
        catch (exception& e)
        {
				cout << "Exception: " << e.what() << "\n";
        }
		catch (...)
		{
			    cout << "Unknown exception." << "\n";
		}
		cout << articles.size() << " taille " << endl;
        return 0;
}
