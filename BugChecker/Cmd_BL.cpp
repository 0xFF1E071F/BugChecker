#include "BugChecker.h"

#include "Cmd.h"
#include "Root.h"

class Cmd_BL : public Cmd
{
public:

	virtual const CHAR* GetId() { return "BL"; }
	virtual const CHAR* GetDesc() { return "List all breakpoints."; }
	virtual const CHAR* GetSyntax() { return "BL (no parameters)"; }

	virtual BcCoroutine Execute(CmdParams& params) noexcept
	{
		auto args = TokenizeArgs(params.cmd, "BL");

		if (args.size() != 1)
		{
			Print("Too many arguments.");
			co_return;
		}

		for (int i = 0; i < Root::I->BreakPoints.size(); i++)
		{
			BreakPoint& bp = Root::I->BreakPoints[i];

			CHAR buffer[64];
			::sprintf(buffer, "%s%02d) %s ",
				i == Root::I->BpHitIndex ? "\n0B" : "\n07",
				i,
				bp.skip ? "*" : " ");

			Print((buffer + bp.cmd).c_str());
		}

		co_return;
	}
};

REGISTER_COMMAND(Cmd_BL)
