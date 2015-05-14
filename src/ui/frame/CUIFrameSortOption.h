#ifndef C_UI_FRAME_SORT_OPTION_H
#define C_UI_FRAME_SORT_OPTION_H

class CUIFrameSortOption
    : public std::unary_function<IUIFrame*, bool>
{
public:
    inline bool operator()(const IUIFrame* lhs, const IUIFrame* rhs) const
    {
        if (lhs->IsEnabled() < rhs->IsEnabled()) return true;
        if (lhs->IsEnabled() > rhs->IsEnabled()) return false;
        if (lhs->IsOccupyingFocus() < rhs->IsOccupyingFocus()) return true;
        if (lhs->IsOccupyingFocus() > rhs->IsOccupyingFocus()) return false;
        return (lhs->GetAccessClock() < rhs->GetAccessClock());
    }
};

#endif // C_UI_FRAME_SORT_OPTION_H
