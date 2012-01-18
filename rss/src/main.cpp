#include <iostream>
#include "export_cfg.hpp"
#include "Feed.hpp"

int main(int argc, char* argv[])
{
	std::string feed_url;
	std::map<std::string, FeedReader::Entry> articles;

	// validate arguments
	if (argc == 2)  {
		feed_url = argv[1];
	} else {
		feed_url = "http://www.ladepeche.fr/rss/39.rss";
	}

	try {
		// init once per process
		FeedReader::Feed::Initialize();

		// create custom feed config with the path of the xsl files
		FeedReader::FeedConfig feedConfig("./xsl");

		// create feed reader
		FeedReader::Feed feedReader(feed_url,feedConfig);

		while (true) {
			// check feed
			feedReader.CheckFeed();

			// get results
			std::cout << "----------Feed---------" << std::endl << "URL: '" << feedReader.GetUrl() << "'" << std::endl;

			// print item elements
			for (FeedReader::Feed::entry_iterator itr = feedReader.begin_entries(); itr != feedReader.end_entries(); itr++) {
				std::cout << "UID : " << itr->UniqueId << std::endl;
				if (articles.find(itr->UniqueId) == articles.end()) {
					articles.insert(std::pair<std::string, FeedReader::Entry>(itr->UniqueId, *itr));
					//TODO: send on ivy
					std::cout << "Ajouté !" << std::endl;
				} else {
					std::cout << "Déjà présent." << std::endl;
				}
			}
			sleep(60);


			/*for (FeedReader::Entry::entry_element_iterator itr2 = itr->begin_entry_elements(); itr2 != itr->end_entry_elements(); ++itr2) 		{
			articles[itr2->first] = itr2->second;
			}*/
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}
	catch (...)
	{
		std::cout << "Unknown exception." << "\n";
	}
	return 0;
}
