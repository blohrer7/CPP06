/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blohrer <blohrer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:51:41 by blohrer           #+#    #+#             */
/*   Updated: 2026/03/12 14:51:46 by blohrer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <cstdlib>
#include <ctime>

int	main(void)
{
	Base	*ptr;
	int		i;

	std::srand(std::time(0));
	i = 0;
	while (i < 10)
	{
		ptr = generate();

		std::cout << "identify(ptr): ";
		identify(ptr);

		std::cout << "identify(*ptr): ";
		identify(*ptr);

		delete ptr;
		std::cout << "----------" << std::endl;
		i++;
	}
	return (0);
}
