Rails.application.routes.draw do
  resources :programs
  resources :thread_objects, path: 'threads'
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
