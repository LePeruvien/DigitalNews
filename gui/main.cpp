#include <QtCore/QTextCodec>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QGraphicsScene>

#include "article.hpp"
#include "button.hpp"
#include "view.hpp"


#include <QtCore/QPropertyAnimation>
#include <QtGui/QPushButton>

int main(int argc, char* argv[]) {
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

	QApplication app(argc, argv);

    const QRect screen = QApplication::desktop()->screenGeometry();
    QGraphicsScene scene(screen);

    Article article;
	article.setContent("Syrie: négociations toujours difficiles au Conseil de sécurité de l'ONU", "Des discussions au Conseil de sécurité de l'ONU sur un projet de résolution russe sur la situation en Syrie ont duré plus de quatre heures mardi, sans que les membres du Conseil n'approchent d'un accord, a-t-on appris auprès de diplomates.\n\nDes experts des 15 pays membres du Conseil ont évoqué le projet russe, au moment où les critiques sur l'inaction de l'ONU face aux violences en Syrie se font croissantes.\n\nLes pays occidentaux s'opposent à la demande russe d'attribuer de manière équitable les violences aux opposants et au régime du président Assad. Les Etats-Unis, la France et l'Allemagne avaient prévenu avant même ces discussions que le projet russe était en l'état inacceptable.\n\n\"Il y a eu plus de quatre heures de discussions, mais elles n'ont porté que sur les paragraphes d'introduction\" du texte, a déclaré un diplomate occidental d'un pays impliqué dans ces négociations.\n\n\"Il n'y a pas vraiment d'effort pour combler le fossé\" séparant les différents points de vue, a commenté un autre diplomate occidental sous couvert d'anonymat.\n\nAprès que la Russie et la Chine ont opposé leur veto à un projet de résolution de l'ONU sur la Syrie en octobre, Moscou a présenté à la mi-décembre un projet de résolution condamnant à la fois la violence du gouvernement et celle de l'opposition. Mais les puissances occidentales ont jugé ce texte trop timoré.\n\nLa répression en Syrie a fait au moins 5.400 morts depuis la mi-mars, selon les Nations unies.", Article::News);

	Article article2;
	article2.setContent("Qu'est-ce que le Lorem Ipsum ?", "Le Lorem Ipsum est simplement du faux texte employé dans la composition et la mise en page avant impression. Le Lorem Ipsum est le faux texte standard de l'imprimerie depuis les années 1500, quand un peintre anonyme assembla ensemble des morceaux de texte pour réaliser un livre spécimen de polices de texte. Il n'a pas fait que survivre cinq siècles, mais s'est aussi adapté à la bureautique informatique, sans que son contenu n'en soit modifié. Il a été popularisé dans les années 1960 grâce à la vente de feuilles Letraset contenant des passages du Lorem Ipsum, et, plus récemment, par son inclusion dans des applications de mise en page de texte, comme Aldus PageMaker.", Article::Culture);


	Article article3;
	article3.setContent("The MVP team kill", "Disappointing, but advancing: Gumiho advanced as many people expected, but his performance was not the most inspiring. His TvT looked flat as usual, but even his vaunted TvZ wasn't looking so sharp. Against Yugioh – who was panned by Tastosis for showing quality of play that belonged in 2010 – Gumiho just barely got through after struggling for three games. Though he made it into the next round, it was still a disappointing outing for a rising player who has played much better in the past. Even FXO Head Coach Choya had to make a tweet to make up for Gumiho's uncharacteristic performance: @FXOChoya \"today , gumiho's condition wasn't good so he didn't play well but , he practice very well and has really good skills so plz look foward to watch his ro16 !\"\n\nLet's not do the time warp again: Tasteless was a little bit too harsh when he said he felt like he was back in GSL Open Season III upon seeing Yugioh's play, but only just a little bit. Facing Gumiho on Crossfire, Yugioh moved his units around the map without a shred of purpose, allowing his Terran opponent to do whatever he wanted. His decisions to engage or back off seemed almost random at certain points in the game, and at no point did it seem like he had a long term strategy for winning. Yugioh has shown he can play much, much better, but at least for one game he seemed completely out of place in 2012.\n\nAn alternative to mech and bio: Mvp makes mech look stupidly solid and reliable in TvT. On the other hand, Polt might convince you that going bio will always let you be one good engagement away from winning the game. However, if we look at MMA's recent TvT games, I think we have a valid third option: Cheese. them. to. death.\nAfter smashing Mvp at Blizzcon with some smart one base all-ins, MMA repeated that performance at the Blizzard Cup with even more cheesy tactics. Against Gumiho, he made it three TvT series in a row where all-ins factored in heavily (he even used one of the same builds he used to beat Mvp).\n\nObviously, MMA can only do this because he has good standard TvT which he can force opponents to prepare for while he goes for something sneaky instead. However, none of the other Terrans with good normal TvT mix in all-ins to the degree of MMA, even though you might think it would let them win a few more games. By my purely anecdotal analysis, it seems that all-ins are underutilized in TvT right now compared to their success rate. Maybe more GSL Terrans should take a leaf from MMA's book and make it a bigger part of their games.", Article::Sport);

	Article article4;
	article4.setContent("Title", "Test d'article un peu long", Article::Economy);

	View v(&scene, screen.size());
    v.showFullScreen();

    v.addArticle(article);
    v.addArticle(article2);
    v.addArticle(article3);

    for (unsigned int i = 3; i < 15; ++i) {
        v.addArticle(article4);
    }

    return app.exec();
}
